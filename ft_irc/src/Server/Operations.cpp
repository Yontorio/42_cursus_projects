#include "Server.hpp"

Client *Server::findClientByNickName(const std::string &nickname)
{
    for (std::map<int,Client*>::iterator it = clientsByFd.begin(); it != clientsByFd.end(); ++it)
    {
        if (strcasecmp((it->second)->getNickname().c_str(), nickname.c_str()) == 0)
        {
            return (it->second);
        }
    }
    return NULL;
}

void Server::changeClientNickname(Client *client, const std::string &newNick)
{
	client->setNickname(newNick);
}

void Server::addClient(Client *client)
{
	clientsByFd[client->getFd()] = client;
}


Client *Server::findClientByFd(int fd)
{
	std::map<int, Client *>::iterator it = clientsByFd.find(fd);
	if (it == clientsByFd.end())
	{
		return NULL;
	}
	return it->second;
}


int Server::removeClient(int fd, const std::string &quitMsg)
{
	Client *client;
	Channel *channel;
	std::string fullQuitMsg;

	client = findClientByFd(fd);
	if (!client)
	{
		return (0);
	}
	fullQuitMsg = ":" + client->getPrefix() + " QUIT :" + quitMsg + "\r\n";
	client->removeFromAllChannelInviteLists();

	std::vector<std::string> channelNames;
	for (Client::channelIterator it = client->beginChannels(); it != client->endChannels(); ++it)
		channelNames.push_back((*it)->getName());

	for (std::vector<std::string>::iterator it = channelNames.begin(); it != channelNames.end(); ++it)
	{
		channel = findChannel(*it);
		if (!channel)
			continue;
		broadcastToChannel(channel, fullQuitMsg, fd);
		channel->removeMember(client);
		if (channel->isEmpty())
			removeChannel(channel);
	}
	epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	close(fd);
	clientsByFd.erase(fd);
	delete client;
	return (0);
}


size_t Server::getClientCount() const
{
	return clientsByFd.size();
}

Channel *Server::findChannel(std::string const &name)
{
	std::map<std::string, Channel *>::iterator it = channels.find(name);
	if (it != channels.end())
		return it->second;
	return NULL;
}

Channel *Server::createChannel(const std::string &name)
{
	Channel *channel;

	channel = new Channel(name);
	addChannel(channel);
	return channel;
}

void Server::addChannel(Channel *channel)
{
	if (channel)
		channels[channel->getName()] = channel;
}

void Server::removeChannel(Channel *channel)
{
	if (channel)
	{
		channels.erase(channel->getName());
		delete channel;
	}
}

void Server::broadcastToChannel(Channel *channel, const std::string &msg, int excludeFd)
{
	std::vector<int> fds;

	for (Channel::memberIterator it = channel->beginMembers(); it != channel->endMembers(); ++it)
	{
		if (it->first->getFd() != excludeFd)
			fds.push_back(it->first->getFd());
	}
	for (std::vector<int>::iterator it = fds.begin(); it != fds.end(); ++it)
	{
		sendData(*it, msg);
	}
}

std::string Server::getNamesList(Channel *channel)
{
	std::string namesList;

	for (Channel::memberIterator it = channel->beginMembers(); it != channel->endMembers(); ++it)
	{
		if (!namesList.empty())
			namesList += " ";
		if (it->second)
			namesList += "@";
		namesList += it->first->getNickname();
	}
	return namesList;
}


size_t Server::getChannelCount() const
{
	return channels.size();
}

std::string Server::getUptimeString() const
{
	std::time_t now = std::time(NULL);
	long seconds = static_cast<long>(now - startTime);
	return Utils::formatDuration(seconds);
}

std::string Server::getChannelNamesString() const
{
	std::string out;
	for (std::map<std::string, Channel *>::const_iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (!out.empty())
			out += " ";
		out += it->first;
	}
	return out;
}

void Server::sendData(int fd, const std::string &message)
{
	Client *client = findClientByFd(fd);
	if (!client)
	{
		return;
	}
	client->queueOutput(message);
	if (flushOutput(client) == -1)
	{
		removeClient(fd, "ERROR");
		return;
	}
	updatePollEvents(fd);
}

void Server::sendData(Client *client, const std::string &message)
{
	client->queueOutput(message);
	if (flushOutput(client) == -1)
	{
		removeClient(client->getFd(), "ERROR");
		return;
	}
	updatePollEvents(client);
}

void Server::	sendReply(Client *client, const std::string &replyCode, const std::string &replyMsg)
{
	std::ostringstream msg;
	msg << ":" << getServerName() << " " << replyCode << " " << client->getNickname() << " " << replyMsg;
	msg << "\r\n";
	sendData(client, msg.str());
}

void Server::sendErrorMsg(Client *client, const std::string &errCode, const std::string &target,
                          const std::string &reason)
{
	if (target.empty())
		sendReply(client, errCode, ":" + reason);
	else
		sendReply(client, errCode, target + " :" + reason);
}


