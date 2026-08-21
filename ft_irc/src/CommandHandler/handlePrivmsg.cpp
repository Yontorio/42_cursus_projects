#include "CommandHandler.hpp"

static int sendToChannel(Server *server, Client *client, const std::string &target,
                         const std::ostringstream &msg, const std::string &text);
static int sendToClient(Server *server, Client *client, const std::string &target,
                        const std::ostringstream &msg);

int CommandHandler::handlePRIVMSG(Server *server, Client *client,
                                  const std::vector<std::string> &args)
{
	const std::string &target = args[0];
	const std::string &text = (args.size() > 1) ? args[1] : "";
	std::ostringstream msg;

	if (target == Bot::getNick())
	{
		Bot::botOnPrivateMsg(server, client, text);
		return (0);
	}
	msg << ":" << client->getPrefix() << " PRIVMSG " << target << " :" << text << "\r\n";
	if (target[0] == '#')
	{
		return (sendToChannel(server, client, target, msg, text));
	}
	else
	{
		return (sendToClient(server, client, target, msg));
	}
}

static int sendToChannel(Server *server, Client *client, const std::string &target,
                         const std::ostringstream &msg, const std::string &text)
{
	Channel *channel = server->findChannel(target);
	if (!channel)
	{
		server->sendErrorMsg(client, ERR_NOSUCHCHANNEL, target, "No such channel");
		return (0);
	}
	if (!channel->hasClient(client))
	{
		server->sendErrorMsg(client, ERR_CANNOTSENDTOCHAN, target, "Cannot send to channel");
		return (0);
	}
	server->broadcastToChannel(channel, msg.str(), client->getFd());
	Bot::botChannelCommand(server, client, channel, text);
	return (0);
}

static int sendToClient(Server *server, Client *client, const std::string &target,
                        const std::ostringstream &msg)
{
	Client *targetClient = server->findClientByNickName(target);
	if (!targetClient)
	{
		server->sendErrorMsg(client, ERR_NOSUCHNICK, target, "No such nick");
		return (0);
	}
	Bot::botDmTracker(client, targetClient);
	server->sendData(targetClient->getFd(), msg.str());
	return (0);
}
