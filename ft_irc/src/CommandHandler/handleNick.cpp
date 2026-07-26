#include "CommandHandler.hpp"

static bool isValidNickname(const std::string &nick);
static bool isNicknameAvailable(Server *server, Client *self, const std::string &nick);
static void acknowledgeNickNameChange(Server *server, Client *client, const std::string &oldPrefix);

int CommandHandler::handleNICK(Server *server, Client *client, const std::vector<std::string> &args)
{
	std::string newNick = args[0];
	const std::string oldNick = client->getNickname();

	if (newNick.length() > Client::MAX_NICK_LENGTH)
	{
		newNick = newNick.substr(0, Client::MAX_NICK_LENGTH);
	}
	if (newNick == oldNick)
	{
		return (0);
	}
	if (!isValidNickname(newNick))
	{
		server->sendErrorMsg(client, ERR_ERRONEUSNICKNAME, newNick, "Erroneous nickname");
		return (0);
	}
	if (!isNicknameAvailable(server, client, newNick))
	{
		server->sendErrorMsg(client, ERR_NICKNAMEINUSE, newNick, "Nickname is already in use");
		return (0);
	}
	const std::string oldPrefix = client->getPrefix();
	server->changeClientNickname(client, newNick);
	if (client->isRegistered())
	{
		acknowledgeNickNameChange(server, client, oldPrefix);
	}
	else if (client->hasRealname())
	{
		client->setRegistered(true);
		server->sendReply(client, RPL_WELCOME,
		                  ":Welcome to the Internet Relay Network Server INTERLINK " +
		                      client->getPrefix());
		Bot::botOnRegisterMsg(server, client);
	}
	return (0);
}

static bool isValidNickname(const std::string &nick)
{
	if (nick.empty() || (!std::isalpha(nick[0]) && std::strchr("[]{}|\\-_^", nick[0]) == NULL))
	{
		return false;
	}
	for (size_t i = 1; i < nick.length(); ++i)
	{
		if (!std::isalnum(nick[i]) && std::strchr("[]{}\\|_-", nick[i]) == NULL)
		{
			return false;
		}
	}
	return true;
}

static bool isNicknameAvailable(Server *server, Client *self, const std::string &nick)
{
	if (strcasecmp(self->getNickname().c_str(), nick.c_str()) == 0)
	{
		return (true);
	}
	if (strcasecmp(Bot::getNick().c_str(), nick.c_str()) == 0)
	{
		return (false);
	}
	return (server->findClientByNickName(nick) == NULL);
}

static void acknowledgeNickNameChange(Server *server, Client *client, const std::string &oldPrefix)
{
	std::ostringstream message;
	std::set<int> recipients;

	message << ":" << oldPrefix << " NICK :" << client->getNickname() << "\r\n";
	recipients.insert(client->getFd());
	for (Client::channelIterator chanIt = client->beginChannels(); chanIt != client->endChannels();
	     ++chanIt)
	{
		for (Channel::memberIterator memIt = (*chanIt)->beginMembers();
		     memIt != (*chanIt)->endMembers(); ++memIt)
		{
			recipients.insert((memIt->first)->getFd());
		}
	}
	for (std::set<int>::iterator it = recipients.begin(); it != recipients.end(); ++it)
	{
		server->sendData(*it, message.str());
	}
}
