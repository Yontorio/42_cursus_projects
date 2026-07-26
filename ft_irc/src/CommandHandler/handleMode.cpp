#include "CommandHandler.hpp"
struct ModeChange
{
	ModeChange(Server *server, Client *client, Channel *channel,
	           const std::vector<std::string> &args)
		: server(server),
		  client(client),
		  channel(channel),
		  args(args),
		  paramIndex(2),
		  sign('+')
	{
	}

	Server *server;
	Client *client;
	Channel *channel;
	const std::vector<std::string> &args;
	std::size_t paramIndex;
	char sign;
	std::string modes;
	std::string params;
};

static void modePrefix(char sign, std::string &outModes)
{
	if (outModes.empty() || outModes[outModes.size() - 1] != sign)
	{
		outModes += sign;
	}
}

static bool parsePositiveInt(const std::string &str, unsigned int &out)
{
	std::istringstream iss(str);
	unsigned long long value = 0;
	char extra = '\0';

	if (!(iss >> value))
	{
		return false;
	}
	if (iss >> extra)
	{
		return false;
	}
	if (value == 0 || value > static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()))
	{
		return false;
	}
	out = static_cast<unsigned int>(value);
	return true;
}

static bool nextModeParam(ModeChange &change, std::string &param)
{
	if (change.paramIndex >= change.args.size())
	{
		return false;
	}
	param = change.args[change.paramIndex++];
	return true;
}

static void rememberAppliedMode(ModeChange &change, char mode)
{
	modePrefix(change.sign, change.modes);
	change.modes += mode;
}

static void sendModeNeedMoreParams(ModeChange &change)
{
	change.server->sendErrorMsg(change.client, ERR_NEEDMOREPARAMS, "MODE",
	                            "Not enough parameters");
}

static void sendInvalidLimitParam(ModeChange &change, const std::string &limitParam)
{
	change.server->sendErrorMsg(change.client, ERR_INVALIDMODEPARAM,
	                            change.channel->getName() + " l " + limitParam,
	                            "Invalid channel limit");
}

static void listChannelModes(Server *server, Client *client, Channel *channel)
{
	std::string modes;
	std::string params;

	if (channel->hasMode('i'))
		modes += "i";
	if (channel->hasMode('t'))
		modes += "t";
	if (channel->hasMode('k'))
	{
		modes += "k";
		params += " " + channel->getPassword();
	}
	if (channel->hasMode('l'))
	{
		std::ostringstream oss;

		oss << channel->getUserLimit();
		modes += "l";
		params += " " + oss.str();
	}
	server->sendReply(client, RPL_CHANNELMODEIS,
	                  channel->getName() + " +" + modes + params);
}

static bool canChangeChannelModes(Server *server, Client *client, Channel *channel)
{
	if (!channel->hasClient(client))
	{
		server->sendErrorMsg(client, ERR_NOTONCHANNEL, channel->getName(),
		 "You're not on that channel");
		return false;
	}
	if (!channel->isOperator(client))
	{
		server->sendErrorMsg(client, ERR_CHANOPRIVSNEEDED, channel->getName(),
		                     "You're not channel operator");
		return false;
	}
	return true;
}

static bool applyNoParamMode(ModeChange &change, char mode)
{
	change.channel->setMode(mode, change.sign == '+');
	return true;
}

static bool applyKeyMode(ModeChange &change)
{
	std::string key;

	if (change.sign == '-')
	{
		nextModeParam(change, key);
		change.channel->clearPassword();
		return true;
	}
	if (!nextModeParam(change, key))
	{
		sendModeNeedMoreParams(change);
		return false;
	}
	change.channel->setPassword(key);
	change.params += " " + key;
	return true;
}

static bool applyLimitMode(ModeChange &change)
{
	std::string limitParam;
	unsigned int limit = 0;

	if (change.sign == '-')
	{
		change.channel->clearUserLimit();
		return true;
	}
	if (!nextModeParam(change, limitParam))
	{
		sendModeNeedMoreParams(change);
		return false;
	}
	if (!parsePositiveInt(limitParam, limit))
	{
		sendInvalidLimitParam(change, limitParam);
		return false;
	}
	change.channel->setUserLimit(limit);

	std::ostringstream oss;
	oss << limit;
	change.params += " " + oss.str();
	return true;
}

static bool applyOperatorMode(ModeChange &change)
{
	std::string nick;

	if (!nextModeParam(change, nick))
	{
		sendModeNeedMoreParams(change);
		return false;
	}
	Client *target = change.server->findClientByNickName(nick);
	if (!target)
	{
		change.server->sendErrorMsg(change.client, ERR_NOSUCHNICK, nick, "No such nick");
		return false;
	}
	if (!change.channel->hasClient(target))
	{
		change.server->sendErrorMsg(change.client, ERR_USERNOTINCHANNEL,
		                            nick + " " + change.channel->getName(),
		                            "They aren't on that channel");
		return false;
	}
	change.channel->setOperator(target, change.sign == '+');
	change.params += " " + nick;
	return true;
}

static void sendUnknownMode(ModeChange &change, char mode)
{
	change.server->sendErrorMsg(change.client, ERR_UNKNOWNMODE, std::string(1, mode),
	                            "is unknown mode char");
}

static bool applyModeChar(ModeChange &change, char mode)
{
	switch (mode)
	{
		case 'i':
		case 't':
			return applyNoParamMode(change, mode);
		case 'k':
			return applyKeyMode(change);
		case 'l':
			return applyLimitMode(change);
		case 'o':
			return applyOperatorMode(change);
		default:
			sendUnknownMode(change, mode);
			return false;
	}
}

static bool applyModeString(ModeChange &change)
{
	const std::string &modeStr = change.args[1];

	for (std::size_t i = 0; i < modeStr.size(); ++i)
	{
		const char mode = modeStr[i];

		if (mode == '+' || mode == '-')
		{
			change.sign = mode;
			continue;
		}
		if (!applyModeChar(change, mode))
		{
			continue;
		}
		rememberAppliedMode(change, mode);
	}
	return true;
}

static void broadcastModeChange(ModeChange &change, const std::string &chanName)
{
	std::ostringstream msg;

	if (change.modes.empty())
	{
		return;
	}
	msg << ":" << change.client->getPrefix() << " MODE " << chanName << " "
	    << change.modes << change.params << "\r\n";
	change.server->broadcastToChannel(change.channel, msg.str(), -1);
}

int CommandHandler::handleMODE(Server *server, Client *client,
                               const std::vector<std::string> &args)
{
	const std::string &chanName = args[0];
	Channel           *channel = server->findChannel(chanName);

	if (!chanName.empty() && chanName[0] != '#')
	{
		return (0);
	}
	if (!channel)
	{
		server->sendErrorMsg(client, ERR_NOSUCHCHANNEL, chanName, "No such channel");
		return (0);
	}
	if (!channel->hasClient(client))
	{
		server->sendErrorMsg(client, ERR_NOTONCHANNEL, channel->getName(),
		                     "You're not on that channel");
		return (0);
	}
	if (args.size() == 1)
	{
		listChannelModes(server, client, channel);
		return (0);
	}
	if (canChangeChannelModes(server, client, channel))
	{
		ModeChange change(server, client, channel, args);
		applyModeString(change);
		broadcastModeChange(change, chanName);
	}
	return (0);
}
