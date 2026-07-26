#include "Server.hpp"

const std::string Server::serverName = "interlink";

const std::string &Server::getServerName()
{
	return serverName;
}

bool Server::isPasswordCorrect(const std::string &password) const
{
	return this->password == password;
}

bool Server::hasPassword() const
{
	return !password.empty();
}

Server::Server(int port, const std::string &password)
	: password(password), port(port),
	  mainSocketFd(-1), epoll_fd(-1),
	  startTime(std::time(NULL))
{
	struct epoll_event event;

	setupSocket();
	if ((epoll_fd = epoll_create1(0)) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = mainSocketFd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, mainSocketFd, &event) == -1)
	{
		throw std::runtime_error(strerror(errno));
	}
}

Server::~Server()
{
}
