#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <map>
# include "Client.hpp"
class User;

class Channel
{
	std::string					name;
	std::string 				password;
	std::string 				topic;
	std::map<Client *, bool>	members;
	std::set<char> 				modes;
	unsigned int 				userLimit;
	std::set<Client *> 			inviteList;
public:
	Channel();
	Channel(std::string name);
	Channel(Channel const &other);
	Channel &operator=(Channel const &other);
	~Channel();
	
	bool isEmpty() const;
	const std::string& getName() const;
	const std::string& getPassword() const;
	unsigned int getUserLimit() const;
	const std::string& getTopic() const;
	
	bool hasMode(char mode) const;
	bool isInviteOnly() const;
	bool isFull() const;
	bool hasClient(Client* client) const;
	bool isOperator(Client* client) const;
	bool isInvited(Client* client) const;
	
	typedef std::map<Client *, bool>::const_iterator memberIterator;
	memberIterator beginMembers() const;
	memberIterator endMembers() const;

	void setTopic(const std::string &newTopic);
	void setMode(char mode, bool value);
	void setPassword(const std::string &newPassword);
	void clearPassword();
	void setUserLimit(unsigned int limit);
	void clearUserLimit();
	void setOperator(Client *client, bool isOperator);
	void addMember(Client* client, bool isOperator = false);
	void removeMember(Client* client);
	void addMemberToInviteList(Client *client);
	void removeMemberFromInviteList(Client *client);
	void addClientToInviteList(Client *client);
	void removeClientFromInviteList(Client *client);
	void removeFromAllInvitedClients();
};

#endif
