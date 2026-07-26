#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "IrcMessageTokenizer.hpp"
#include "NumericReplies.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Bot.hpp"
#include "Utils.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

class Server;
class Channel;
class CommandHandler
{
  private:
	// Prevent instantiation of purely static class
	CommandHandler();
	CommandHandler(CommandHandler const &other);
	CommandHandler &operator=(CommandHandler const &other);
	~CommandHandler();

	typedef int (*CmdFunc)(Server *, Client *, std::vector<std::string> const&);

	struct CommandInfo
	{
		CmdFunc func;
		bool    needsAuth;
		bool    needsRegistered;
		size_t  minArgs;
	};

	static std::map<std::string, CommandInfo> dispatch;
	static void initDispatch();
	static CommandInfo makeCmd(CmdFunc func, bool needsAuth, bool needsRegistered, size_t minArgs);
	static int handlePASS(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleNICK(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleUSER(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleJOIN(Server *server, Client *client, const std::vector<std::string> &args);
	static int handlePRIVMSG(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleKICK(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleINVITE(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleTOPIC(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleMODE(Server *server, Client *client, const std::vector<std::string> &args);
	static int handleCAP(Server *server, Client *client, const std::vector<std::string> &args);
	static int handlePING(Server *server, Client *client, const std::vector<std::string> &args);

  public:
	static int handle(Server *server, Client *client, const std::string &cmd);
};

#endif
