#include "CommandHandler.hpp"

int CommandHandler::handlePING(Server *server, Client *client, const std::vector<std::string> &args)
{
	if (args.empty())
	{
		server->sendErrorMsg(client, ERR_NEEDMOREPARAMS, "PING", "Not enough parameters");
		return (0);
	}
	std::ostringstream msg;
	msg << "PONG " << args[0] << "\r\n";
	server->sendData(client->getFd(), msg.str());
	return (0);
}
