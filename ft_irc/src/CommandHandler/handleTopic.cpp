#include "CommandHandler.hpp"

static void listTopic(Server *server, Channel *channel, Client *client);
static void changeTopic(Server *server, Channel *channel, Client *client,
							 const std::string &topic);
							 
int CommandHandler::handleTOPIC(Server *server, Client *client, const std::vector<std::string> &args)
{
	const std::string &chanName = args[0];
	Channel           *channel;

	channel = server->findChannel(chanName);
	if (!channel)
	{
		server->sendErrorMsg(client, ERR_NOSUCHCHANNEL, chanName, "No such channel");
		return (0);
	}
	if (!channel->hasClient(client))
	{
		server->sendErrorMsg(client, ERR_NOTONCHANNEL, chanName, "You're not on that channel");
		return (0);
	}
	if (args.size() == 1)
	{
		listTopic(server, channel, client);
	}
	else
	{
		changeTopic(server, channel, client, args[1]);
	}
	return (0);
}

static void listTopic(Server *server, Channel *channel, Client *client)
{
	if (channel->getTopic().empty())
	{
		server->sendReply(client, RPL_NOTOPIC, channel->getName() + " :No topic is set");
	}
	else
	{
		server->sendReply(client, RPL_TOPIC, channel->getName() + " :" + channel->getTopic());
	}
}

static void changeTopic(Server *server, Channel *channel, Client *client,
							 const std::string &topic)
{
	std::ostringstream msg;

	if (channel->hasMode('t') && !channel->isOperator(client))
	{
		server->sendErrorMsg(client, ERR_CHANOPRIVSNEEDED, channel->getName(),
		                     "You're not channel operator");
		return;
	}
	channel->setTopic(topic);
	msg << ":" << client->getPrefix() << " TOPIC " << channel->getName() << " :" << topic
	    << "\r\n";
	server->broadcastToChannel(channel, msg.str(), -1);
}
