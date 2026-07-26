#include "CommandHandler.hpp"

int CommandHandler::handleUSER(Server *server, Client *client, const std::vector<std::string> &args)
{
	if (client->isRegistered())
	{
		server->sendErrorMsg(client, ERR_ALREADYREGISTERED, "",
		                     "Unauthorized command (already registered)");
		return (0);
	}
	client->setUsername(args[0]);
	client->setRealname(args[3]);
	if (client->hasNickname())
	{
		client->setRegistered(true);
		server->sendReply(client, RPL_WELCOME,
		                  ":Welcome to the Internet Relay Network Server INTERLINK " + client->getPrefix()); //
		Bot::botOnRegisterMsg(server, client);
	}
	return (0);
}
