#include "Client.hpp"
#include "Channel.hpp"

Client::Client(int fd, const std::string &ip) : fd(fd), ip(ip)
{
	nickname = "*";
	authenticated = false;
	registered = false;
}


Client::~Client()
{
}

int Client::getFd() const
{
	return fd;
}

const std::string &Client::getIp() const
{
	return ip;
}

size_t Client::getInputBufferSize() const
{
	return inputBuffer.size();
}

const std::string &Client::getNickname() const
{
	return nickname;
}

const std::string &Client::getUsername() const
{
	return username;
}

const std::string &Client::getRealname() const
{
	return realname;
}

const std::string &Client::getPassword() const
{
	return password;
}

bool Client::hasNickname() const
{
	return nickname != "*" && !nickname.empty();
}

bool Client::hasRealname() const
{
	return !realname.empty();
}

const std::string &Client::getOutputBuffer() const
{
	return outputBuffer;
}

bool Client::hasPendingOutput() const
{
	return !outputBuffer.empty();
}

bool Client::isAuthenticated() const
{
	return authenticated;
}

bool Client::isRegistered() const
{
	return registered;
}
const std::set<Channel *> &Client::getChannels() const
{
	return channels;
}
const std::set<Channel *> &Client::getInvitedChannels() const
{
	return invitedTo;
}
Client::channelIterator Client::beginChannels()
{
	return channels.begin();
}
Client::channelIterator Client::endChannels()
{
	return channels.end();
}
std::string Client::getPrefix() const
{
	return nickname + "!" + username + "@" + ip;
}

void Client::setNickname(const std::string &nick)
{
	nickname = nick;
}

void Client::setUsername(const std::string &user)
{
	username = user;
}

void Client::setRealname(const std::string &real)
{
	realname = real;
}

void Client::setPassword(const std::string &pass)
{
	password = pass;
}

void Client::setAuthenticated(bool state)
{
	authenticated = state;
}

void Client::setRegistered(bool state)
{
	registered = state;
}

void Client::addToInputBuffer(char const *data, size_t len)
{
	inputBuffer.append(data, len);
}

void Client::queueOutput(const std::string &data)
{
	outputBuffer.append(data);
}

void Client::consumeOutput(size_t len)
{
	outputBuffer.erase(0, len);
}

void Client::clearInputBuffer()
{
	inputBuffer.clear();
}

std::string Client::extractLine()
{
	size_t pos;
	std::string cmd;

	pos = inputBuffer.find("\r\n");
	if (pos == std::string::npos)
	{
		return "";
	}
	cmd = inputBuffer.substr(0, pos + 2);
	inputBuffer.erase(0, cmd.size());
	return (cmd);
}

void Client::joinChannel(Channel *channel)
{
	channels.insert(channel);
	removeChannelFromInviteList(channel);

}

void Client::leaveChannel(Channel *channel)
{
	channels.erase(channel);
}

void Client::addChannelToInviteList(Channel *channel)
{
	invitedTo.insert(channel);
}

void Client::removeChannelFromInviteList(Channel *channel)
{
	invitedTo.erase(channel);
}

void Client::removeFromAllChannelInviteLists()
{
	for (std::set<Channel *>::iterator it = invitedTo.begin(); it != invitedTo.end(); ++it)
	{
		(*it)->removeMemberFromInviteList(this);
	}
	invitedTo.clear();
}

bool Client::isInvitedTo(Channel *channel) const
{
	return invitedTo.find(channel) != invitedTo.end();
}
