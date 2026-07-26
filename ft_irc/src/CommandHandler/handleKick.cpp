#include "CommandHandler.hpp"

static void removeUserFromChannel(Server *server, Channel *channel, Client *client,
								  const std::vector<std::string> &targetUsers,
								  const std::string &comment);

// KICK <channel> <user> *( "," <user> ) [<comment>]

int CommandHandler::handleKICK(Server *server, Client *client, const std::vector<std::string> &args)
{
	const std::string &chanName = args[0];
	Channel *channel;
	std::vector<std::string> targetUsers;
	const std::string &comment = (args.size() > 2) ? args[2] : "Requested by channel operator";

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
	if (!channel->isOperator(client))
	{
		server->sendErrorMsg(client, ERR_CHANOPRIVSNEEDED, chanName, "You're not channel operator");
		return (0);
	}
	Utils::splitString(targetUsers, args[1], ',');
	removeUserFromChannel(server, channel, client, targetUsers, comment);
	return (0);
}

static void removeUserFromChannel(Server *server, Channel *channel, Client *client,
								  const std::vector<std::string> &targetUsers,
								  const std::string &comment)
{

	for (size_t i = 0; i < targetUsers.size(); ++i)
	{
		const std::string &targetNick = targetUsers[i];
		Client *targetClient = server->findClientByNickName(targetNick);
		if (!targetClient || !channel->hasClient(targetClient))
		{
			server->sendErrorMsg(client, ERR_USERNOTINCHANNEL,
								 targetNick + " " + channel->getName(),
								 "They aren't on that channel");
			continue;
		}
		std::ostringstream msg;
		msg << ":" << client->getPrefix() << " KICK "
			<< channel->getName() << " " << targetNick << " :" << comment << "\r\n";
		server->broadcastToChannel(channel, msg.str(), -1);
		channel->removeMember(targetClient);
		if (channel->isEmpty())
		{
			server->removeChannel(channel);
			break;
		}
		if (targetClient == client)
		{
			break;
		}
	}
}
