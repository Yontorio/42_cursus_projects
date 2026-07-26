#include "CommandHandler.hpp"
#include "Client.hpp"
#include "IrcMessageTokenizer.hpp"
#include "NumericReplies.hpp"
#include "Server.hpp"
#include "Utils.hpp"

std::map<std::string, CommandHandler::CommandInfo> CommandHandler::dispatch;

CommandHandler::CommandInfo CommandHandler::makeCmd(CmdFunc func, bool needsAuth,
                                                    bool needsRegistered, size_t minArgs)
{
	CommandInfo cmd;
	cmd.func = func;
	cmd.needsAuth = needsAuth;
	cmd.needsRegistered = needsRegistered;
	cmd.minArgs = minArgs;
	return cmd;
}

void CommandHandler::initDispatch()
{
	if (!dispatch.empty())
	{
		return;
	}
	dispatch["PASS"]    = makeCmd(&handlePASS,    false, false, 1);
	dispatch["NICK"]    = makeCmd(&handleNICK,    true,  false, 1);
	dispatch["USER"]    = makeCmd(&handleUSER,    true,  false, 4);
	dispatch["JOIN"]    = makeCmd(&handleJOIN,    true,  true,  1);
	dispatch["PRIVMSG"] = makeCmd(&handlePRIVMSG, true,  true,  2);
	dispatch["KICK"]    = makeCmd(&handleKICK,    true,  true,  2);
	dispatch["INVITE"]  = makeCmd(&handleINVITE,  true,  true,  2);
	dispatch["TOPIC"]   = makeCmd(&handleTOPIC,   true,  true,  1);
	dispatch["MODE"]    = makeCmd(&handleMODE,    true,  true,  1);
	dispatch["PING"]    = makeCmd(&handlePING,    false, false, 1);
}

int CommandHandler::handle(Server *server, Client *client, const std::string &line)
{
	ParsedMessage                                    msg;
	std::map<std::string, CommandInfo>::iterator     it;

	initDispatch();
	IrcMessageTokenizer::parse(line, msg);
	if (msg.command.empty())
	{
		return (0);
	}
	Utils::stringToUpper(msg.command);
	it = dispatch.find(msg.command);
	if (it == dispatch.end())
	{
		server->sendErrorMsg(client, ERR_UNKNOWNCOMMAND, msg.command, "Unknown command");
		return (0);
	}
	const CommandInfo &info = it->second;
	if (info.needsAuth && server->hasPassword() && !client->isAuthenticated())
	{
		server->sendErrorMsg(client, ERR_NOTREGISTERED, "", "You have not registered");
		return (0);
	}
	if (info.needsRegistered && !client->isRegistered())
	{
		server->sendErrorMsg(client, ERR_NOTREGISTERED, "", "You have not registered");
		return (0);
	}
	if (msg.args.size() < info.minArgs)
	{
		server->sendErrorMsg(client, ERR_NEEDMOREPARAMS, msg.command, "Not enough parameters");
		return (0);
	}
	return info.func(server, client, msg.args);
}
