#include "Channel.hpp"

Channel::Channel() : userLimit(0)
{
	modes.insert('t');
}

Channel::Channel(std::string name) : name(name), userLimit(0)
{
	modes.insert('t');
}

Channel::Channel(Channel const &other) //
{
	(void)other;
}

Channel &Channel::operator=(Channel const &other)
{
	(void)other;
	return (*this);
}

Channel::~Channel()
{
	removeFromAllInvitedClients();
	members.clear();
}

bool Channel::isEmpty() const
{
	return members.empty();
}
const std::string &Channel::getName() const
{
	return name;
}
const std::string &Channel::getPassword() const
{
	return password;
}
unsigned int Channel::getUserLimit() const
{
	return userLimit;
}
const std::string &Channel::getTopic() const
{
	return topic;
}

bool Channel::hasMode(char mode) const
{
	return modes.find(mode) != modes.end();
}
bool Channel::isInviteOnly() const
{
	return hasMode('i');
}
bool Channel::isFull() const
{
	return hasMode('l') && userLimit > 0 && members.size() >= userLimit;
}
bool Channel::hasClient(Client *client) const
{
	return members.find(client) != members.end();
}
bool Channel::isOperator(Client *client) const
{
	std::map<Client *, bool>::const_iterator it = members.find(client);
	if (it != members.end())
		return it->second;
	return false;
}
bool Channel::isInvited(Client *client) const
{
	return inviteList.find(client) != inviteList.end();
}

Channel::memberIterator Channel::beginMembers() const
{
	return members.begin();
}
Channel::memberIterator Channel::endMembers() const
{
	return members.end();
}

void Channel::setTopic(const std::string &newTopic)
{
	this->topic = newTopic;
}

void Channel::setMode(char mode, bool value)
{
	if (value)
		modes.insert(mode);
	else
		modes.erase(mode);
}

void Channel::setPassword(const std::string &newPassword)
{
	password = newPassword;
	setMode('k', true);
}

void Channel::clearPassword()
{
	password.clear();
	setMode('k', false);
}

void Channel::setUserLimit(unsigned int limit)
{
	if (limit == 0)
	{
		clearUserLimit();
		return;
	}
	userLimit = limit;
	setMode('l', true);
}

void Channel::clearUserLimit()
{
	userLimit = 0;
	setMode('l', false);
}

void Channel::setOperator(Client *client, bool isOperator)
{
	std::map<Client *, bool>::iterator it = members.find(client);
	if (it != members.end())
	{
		it->second = isOperator;
	}
}

void Channel::addMember(Client *client, bool isOperator)
{
	if (!hasClient(client))
	{
		members[client] = isOperator;
		client->joinChannel(this);
		removeMemberFromInviteList(client);
	}
}

void Channel::removeMember(Client *client)
{
	if (hasClient(client))
	{
		client->leaveChannel(this);
		members.erase(client);
	}
}

void Channel::addMemberToInviteList(Client *client)
{
	inviteList.insert(client);
}
void Channel::removeMemberFromInviteList(Client *client)
{
	inviteList.erase(client);
}

void Channel::addClientToInviteList(Client *client)
{
	inviteList.insert(client);
}

void Channel::removeClientFromInviteList(Client *client)
{
	inviteList.erase(client);
}

void Channel::removeFromAllInvitedClients()
{
	for (std::set<Client *>::iterator it = inviteList.begin(); it != inviteList.end(); ++it)
	{
		(*it)->removeChannelFromInviteList(this);
	}
	inviteList.clear();
}
