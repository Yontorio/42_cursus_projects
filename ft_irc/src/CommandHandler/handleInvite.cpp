#include "CommandHandler.hpp"

static bool canInvite(Server *server, Client *client, Channel *channel,
	                    const std::string &targetNick, Client *&target);

int CommandHandler::handleINVITE(Server *server, Client *client, const std::vector<std::string> &args)
{
	const std::string &targetNick = args[0];
	const std::string &chanName = args[1];
	Client  *target;
	Channel *channel = server->findChannel(chanName);

	if (!channel)
	{
		server->sendErrorMsg(client, ERR_NOSUCHCHANNEL, chanName, "No such channel");
		return (0);
	}
	if (!canInvite(server, client, channel, targetNick, target))
	{
		return (0);
	}
	channel->addMemberToInviteList(target);
	target->addChannelToInviteList(channel);
	server->sendReply(client, RPL_INVITING, targetNick + " :" + chanName);
	server->sendData(target, ":" + client->getPrefix() + " INVITE " + targetNick + " :" + chanName + "\r\n");
	return (0);
}

static bool canInvite(Server *server, Client *client, Channel *channel,
	                    const std::string &targetNick, Client *&target)
{
	if (!channel->hasClient(client))
	{
		server->sendErrorMsg(client, ERR_NOTONCHANNEL, channel->getName(), "You're not on that channel");
		return false;
	}
	if (!channel->isOperator(client))
	{
		server->sendErrorMsg(client, ERR_CHANOPRIVSNEEDED, channel->getName(), "You're not channel operator");
		return false;
	}
	target = server->findClientByNickName(targetNick);
	if (!target)
	{
		server->sendErrorMsg(client, ERR_NOSUCHNICK, targetNick, "No such nick");
		return false;
	}
	if (channel->hasClient(target))
	{
		server->sendErrorMsg(client, ERR_USERONCHANNEL, targetNick + " " + channel->getName(), "is already on channel");
		return false;
	}
	return true;
}
