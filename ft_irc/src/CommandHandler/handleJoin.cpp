#include "CommandHandler.hpp"


static void joinSingleChannel(Server *server, Client *client, const std::string &chanName,
                               const std::string &key);
static bool canJoinChannel(Server *server, Client *client, Channel *channel,
	                        const std::string &key);
							static void sendTopicReply(Server *server, Client *client, Channel *channel);
static void broadcastJoinMsg(Server *server, Client *client, Channel *channel);
static void sendNamesList(Server *server, Client *client, Channel *channel);

int CommandHandler::handleJOIN(Server *server, Client *client, const std::vector<std::string> &args)
{
	std::vector<std::string> channels;
	std::vector<std::string> keys;
	const std::string        noKey = "";

	Utils::splitString(channels, args[0], ',');
	if (args.size() > 1)
	{
		Utils::splitString(keys, args[1], ',');
	}
	for (size_t i = 0; i < channels.size(); ++i)
	{
		const std::string &key = (i < keys.size()) ? keys[i] : noKey;
		joinSingleChannel(server, client, channels[i], key);
	}
	return (0);
}

static void joinSingleChannel(Server *server, Client *client, const std::string &chanName,
                               const std::string &key)
{
	Channel	*channel;
	bool     isNewChannel, isOperator;

	if (chanName.empty()) // JOIN : on connect;
	{
		return;
	}
	if ((chanName[0] != '#'))
	{
		server->sendErrorMsg(client, ERR_NOSUCHCHANNEL, chanName, "No such channel");
		return;
	}
	channel = server->findChannel(chanName);
	isNewChannel = false;
	if (!channel)
	{
		channel = server->createChannel(chanName);
		isNewChannel = true;
	}
	if (channel->hasClient(client))
	{
		return;
	}
	if (!isNewChannel && !canJoinChannel(server, client, channel, key))
	{
		return;
	}
	isOperator = isNewChannel;
	channel->addMember(client, isOperator);
	broadcastJoinMsg(server, client, channel);
	sendTopicReply(server, client, channel);
	sendNamesList(server, client, channel);
	Bot::botOnJoinMsg(server, client, channel);
}

static bool canJoinChannel(Server *server, Client *client, Channel *channel,
	                        const std::string &key)
{
	if (channel->hasMode('k') && channel->getPassword() != key)
	{
		server->sendErrorMsg(client, ERR_BADCHANNELKEY, channel->getName(),
		                     "Cannot join channel (+k)");
		return false;
	}
	if (channel->isFull())
	{
		server->sendErrorMsg(client, ERR_CHANNELISFULL, channel->getName(),
		                     "Cannot join channel (+l)");
		return false;
	}
	if (channel->isInviteOnly() && !channel->isInvited(client))
	{
		server->sendErrorMsg(client, ERR_INVITEONLYCHAN, channel->getName(),
		                     "Cannot join channel (+i)");
		return false;
	}
	return true;
}

static void broadcastJoinMsg(Server *server, Client *client, Channel *channel)
{
	std::ostringstream msg;

	msg << ":" << client->getPrefix() << " JOIN :" << channel->getName() << "\r\n";
	server->broadcastToChannel(channel, msg.str(), -1);
}

static void sendTopicReply(Server *server, Client *client, Channel *channel)
{
	if (channel->getTopic().empty())
		return;
	server->sendReply(client, RPL_TOPIC, channel->getName() + " :" + channel->getTopic());
}

static void sendNamesList(Server *server, Client *client, Channel *channel)
{
	std::string namesList;

	namesList = server->getNamesList(channel);
	server->sendReply(client, RPL_NAMREPLY, "= " + channel->getName() + " :" + namesList);
	server->sendReply(client, RPL_ENDOFNAMES, channel->getName() + " :End of /NAMES list.");
}
