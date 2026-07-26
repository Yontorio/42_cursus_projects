#include "Bot.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

#include <sstream>

const std::string &Bot::getNick()
{
	static const std::string nick = "MrBot";
	return nick;
}

std::string Bot::buildPrefix()
{
	return getNick() + "!bot@" + Server::getServerName();
}

bool Bot::isChannelTarget(const std::string &target)
{
	return !target.empty() && target[0] == '#';
}

void Bot::sendPrivateMsg(Server *server, const std::string &target, const std::string &text)
{
	std::ostringstream msg;
	msg << ":" << buildPrefix() << " PRIVMSG " << target << " :" << text << "\r\n";

	if (isChannelTarget(target))
	{
		Channel *channel = server->findChannel(target);
		if (channel)
			server->broadcastToChannel(channel, msg.str(), -1);
		return;
	}
	Client *targetClient = server->findClientByNickName(target);
	if (targetClient)
		server->sendData(targetClient->getFd(), msg.str());
}

void Bot::replyMultiLine(Server *server, const std::string &replyTarget, const std::string &text)
{
	std::string::size_type start = 0;
	while (start < text.size())
	{
		std::string::size_type end = text.find('\n', start);
		if (end == std::string::npos)
			end = text.size();
		std::string line = text.substr(start, end - start);
		if (!line.empty())
			sendPrivateMsg(server, replyTarget, line);
		start = end + 1;
	}
}
