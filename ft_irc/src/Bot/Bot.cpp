#include "Bot.hpp"

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Utils.hpp"

static bool startsWith(const std::string &s, const std::string &prefix)
{
	return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

void Bot::botOnRegisterMsg(Server *server, Client *client)
{
	if (!server || !client)
		return;
	replyMultiLine(server, client->getNickname(),
	               "Welcome to INTERLINK server!\n"
	               "Type help anytime to see what I can do!");
}

void Bot::botOnJoinMsg(Server *server, Client *client, Channel *channel)
{
	if (!server || !client || !channel)
		return;
	sendPrivateMsg(server, channel->getName(),
	            "Welcome to " + channel->getName() + " " + client->getNickname()
					+ ". Type ?MrBot anytime to see what I can do!");
}

void Bot::botOnPrivateMsg(Server *server, Client *sender, const std::string &text)
{
	if (!server || !sender)
		return;
	handleCommand(server, sender, sender->getNickname(), text);
}

void Bot::botChannelCommand(Server *server, Client *sender, Channel *channel, const std::string &text)
{
	if (!server || !sender || !channel)
		return;
	std::string trimmed = Utils::ltrimSpaces(text);
	const std::string trigger = "?" + getNick();
	if (!startsWith(trimmed, trigger))
		return;
	if (trimmed.size() > trigger.size() && trimmed[trigger.size()] != ' ')
		return;
	std::string rest = trimmed.substr(trigger.size());
	rest = Utils::ltrimSpaces(rest);
	handleCommand(server, sender, channel->getName(), rest);
}
