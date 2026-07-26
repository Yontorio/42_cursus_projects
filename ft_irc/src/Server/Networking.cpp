#include "Server.hpp"


void Server::setupSocket()
{
	struct sockaddr_in ipv4Addr;
	int reuse = 1;

	std::memset(&ipv4Addr, 0, sizeof ipv4Addr);
	ipv4Addr.sin_port = htons(port);
	ipv4Addr.sin_addr.s_addr = INADDR_ANY;
	ipv4Addr.sin_family = AF_INET;
	mainSocketFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (mainSocketFd == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	if (setsockopt(mainSocketFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	if (bind(mainSocketFd,  reinterpret_cast<struct sockaddr *>(&ipv4Addr), sizeof ipv4Addr) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	if (listen(mainSocketFd, 1024) == -1)
	{
		throw std::runtime_error(std::strerror(errno));
	}
}

void Server::acceptConnections()
{
	struct sockaddr_in addr;
	int fd;
	socklen_t socklen = sizeof addr;
	char buf[INET_ADDRSTRLEN];
	std::string ip;
	struct epoll_event event;

	event.events = EPOLLIN;
	while
	(
		(fd = accept(mainSocketFd, reinterpret_cast<struct sockaddr *>(&addr), &socklen)) != -1
	)
	{
		event.data.fd = fd;
		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1)
		{
			close(fd);
			continue;
		}
		inet_ntop(AF_INET, &addr.sin_addr, buf, sizeof(buf));
		ip = buf;
		addClient(new Client(fd, ip));
		socklen = sizeof addr;
	}
}

void Server::updatePollEvents(int fd)
{
	Client *client = findClientByFd(fd);
	struct epoll_event event;

	if (!client)
	{
		return;
	}
	event.events = EPOLLIN;
	if (client->hasPendingOutput())
	{
		event.events |= EPOLLOUT;
	}
	event.data.fd = fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event) == -1)
	{
		removeClient(fd);
	}
}

void Server::updatePollEvents(Client *client)
{
	struct epoll_event event;

	event.events = EPOLLIN;
	if (client->hasPendingOutput())
	{
		event.events |= EPOLLOUT;
	}
	event.data.fd = client->getFd();
	if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, client->getFd(), &event) == -1)
	{
		removeClient(client->getFd(), "Server ERROR");
	}
}

int Server::flushOutput(Client *client)
{
	while (client->hasPendingOutput())
	{
		const std::string &buffer = client->getOutputBuffer();
		ssize_t sent = send(client->getFd(), buffer.c_str(), buffer.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
		if (sent > 0)
		{
			client->consumeOutput(static_cast<size_t>(sent));
			continue;
		}
		if (sent == -1 && (errno == EWOULDBLOCK))
		{
			return 0;
		}
		return -1;
	}
	return 0;
}

static bool isMessageTooLong(size_t bufferedSize, size_t incomingSize)
{
	return (bufferedSize + incomingSize > Server::MAX_MSG_LEN);
}

int Server::receiveData(int fd)
{
	char buf[512];
	ssize_t bytesRead;
	Client *client;
	std::string data;

	client = findClientByFd(fd);
	if (!client)
	{
		return (-1);
	}
	const size_t inputBufferSize = client->getInputBufferSize();
	while (true)
	{
		bytesRead = recv(fd, buf, sizeof(buf), MSG_DONTWAIT);
		if (bytesRead == 0 || (bytesRead == -1 && errno != EWOULDBLOCK))
		{
			removeClient(fd, bytesRead == 0 ? "QUIT" : "ERROR");
			return (-1);
		}
		if (bytesRead == -1 && errno == EWOULDBLOCK)
		{
			break;
		}
		data.append(buf, bytesRead);
		if (isMessageTooLong(inputBufferSize, data.size()))
		{
			removeClient(fd, "Spam");
			return (-1);
		}
	}
	client->addToInputBuffer(data.c_str(), data.size());
	return (0);
}

int Server::executeCmds(int fd)
{
	std::string cmd;
	int status;

	Client *client = findClientByFd(fd);
	if (!client)
	{
		return (-1);
	}
	while (true)
	{
		cmd = client->extractLine();
		if (cmd.empty())
		{
			return (1);
		}


		status = CommandHandler::handle(this, client, cmd);
		if (status == -1)
		{
			removeClient(client->getFd());
			return (-1);
		}
	}
}

void Server::handleReadyPollFd(const struct epoll_event &event)
{
	const int fd = event.data.fd;
	const short revents = event.events;

	if (revents & (EPOLLERR | EPOLLHUP))
	{
		removeClient(fd);
		return;
	}
	if (revents & EPOLLIN)
	{
		if (receiveData(fd) == -1)
		{
			return;
		}
		if (executeCmds(fd) == -1)
		{
			return;
		}
	}
	if (revents & EPOLLOUT)
	{
		Client *client = findClientByFd(fd);
		if (client && flushOutput(client) == -1)
		{
			removeClient(fd, "ERROR");
			return;
		}
		updatePollEvents(fd);
	}
}

void Server::run()
{
	int eventsCount;
	struct epoll_event events[MAX_EPOLL_EVENTS];
	int i;

	while (true)
	{
		eventsCount = epoll_wait(epoll_fd, events, MAX_EPOLL_EVENTS, -1);
		if (eventsCount == -1)
		{
			continue;
		}
		for (i = 0; i < eventsCount; ++i)
		{
			if (events[i].data.fd == mainSocketFd)
				acceptConnections();
			else
				handleReadyPollFd(events[i]);
		}
	}
}
