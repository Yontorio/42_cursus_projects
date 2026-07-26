#include "CommandHandler.hpp"

int CommandHandler::handlePASS(Server *server, Client *client, const std::vector<std::string> &args)
{
	if (client->isAuthenticated())
	{
		server->sendErrorMsg(client, ERR_ALREADYREGISTERED, "",
		                     "Unauthorized command (already registered)");
	}
	else if (!server->isPasswordCorrect(args[0]))
	{
		server->sendErrorMsg(client, ERR_PASSWDMISMATCH, "", "Password incorrect");
		return (-1);
	}
	client->setAuthenticated(true);
	return (0);
}