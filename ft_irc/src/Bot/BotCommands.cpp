#include "Bot.hpp"

#include "Client.hpp"
#include "NumericReplies.hpp"
#include "Server.hpp"
#include "Utils.hpp"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <map>
#include <sstream>
#include <vector>

static std::map<std::string, std::map<std::string, std::string> > unreadDmsByNick;

static void splitCmdArgs(const std::string &str, std::vector<std::string> &out)
{
	std::istringstream iss(str);
	std::string word;
	std::string rest;

	out.clear();
	while (out.size() < 2 && iss >> word)
		out.push_back(word);
	if (out.size() == 2 && std::getline(iss, rest))
	{
		if (!rest.empty() && rest[0] == ' ')
			rest.erase(0, 1);
		if (!rest.empty())
			out.push_back(rest);
	}
}

void Bot::handleCommand(Server *server, Client *sender, const std::string &replyTarget,
                        const std::string &commandText)
{
	std::vector<std::string> words;
	splitCmdArgs(Utils::ltrimSpaces(commandText), words);
	std::string cmd = words.empty() ? "help" : Utils::toLower(words[0]);

	if (cmd == "help")
		handleHelpCommand(server, replyTarget);
	else if (cmd == "time")
		handleTimeCommand(server, replyTarget);
	else if (cmd == "stats")
		handleStatsCommand(server, replyTarget);
	else if (cmd == "inbox")
		handleInBoxCommand(server, sender, replyTarget);
	else if (cmd == "tell")
		handleTellCommand(server, sender, replyTarget, words);
	else if (cmd == "roll")
		handleRollCommand(server, replyTarget, words);
	else if (cmd == "poll")
		handlePollCommand(server, sender, replyTarget, words);
	else
		sendPrivateMsg(server, replyTarget, "Unknown command. Try: help");
}

void Bot::handleHelpCommand(Server *server, const std::string &replyTarget)
{
	replyMultiLine(server, replyTarget,
		"[Help] MrBot Commands:\n"
		"[Help]   help                  - Show this help menu\n"
		"[Help]   time                  - Show the current server time\n"
		"[Help]   stats                 - Show server statistics\n"
		"[Help]   roll [sides]          - Roll a die (default: 6-sided)\n"
		"[Help]   inbox                 - View unread messages\n"
		"[Help]   tell <nick> <message> - Send an anonymous message\n"
		"[Help]   poll                  - Show the active poll\n"
		"[Help]   poll start <question> - Start a new poll\n"
		"[Help]   poll yes/no           - Vote yes or no\n"
		"[Help]   poll result           - Show poll results\n"
		"[Help]   poll end              - End the current poll");
}

void Bot::handleTimeCommand(Server *server, const std::string &replyTarget)
{
	sendPrivateMsg(server, replyTarget, "[Time] Server time: " + Utils::getCurrentDateTime());
}

void Bot::handleStatsCommand(Server *server, const std::string &replyTarget)
{
	std::string stats = "[Stats] Clients: " + Utils::toString(server->getClientCount()) +
	                    ", Channels: " + Utils::toString(server->getChannelCount()) +
	                    ", Uptime: " + server->getUptimeString();
	sendPrivateMsg(server, replyTarget, stats);
}

void Bot::handleInBoxCommand(Server *server, Client *sender, const std::string &replyTarget)
{
	if (isChannelTarget(replyTarget))
	{
		sendPrivateMsg(server, replyTarget, "[Inbox] This command is only available in private messages.");
		return;
	}

	std::map<std::string, std::map<std::string, std::string> >::iterator it =
		unreadDmsByNick.find(sender->getNickname());

	if (it == unreadDmsByNick.end() || it->second.empty())
	{
		sendPrivateMsg(server, replyTarget, "[Inbox] No unread direct messages.");
		return;
	}
	sendPrivateMsg(server, replyTarget, "[Inbox] Unread DM senders (latest time per sender):");
	for (std::map<std::string, std::string>::const_iterator sit = it->second.begin();
	     sit != it->second.end(); ++sit)
	{
		sendPrivateMsg(server, replyTarget, "[Inbox] - " + sit->first + " at " + sit->second);
	}
	// it->second.clear();
	unreadDmsByNick.erase(it);
}

void Bot::botDmTracker(Client *sender, Client *target)
{
	if (!sender || !target)
		return;

	unreadDmsByNick[target->getNickname()][sender->getNickname()] = Utils::getCurrentDateTime();
}

void Bot::handleTellCommand(Server *server, Client *sender, const std::string &replyTarget,
                            const std::vector<std::string> &words)
{
	if (isChannelTarget(replyTarget))
	{
		sendPrivateMsg(server, replyTarget, "[Tell] This command is only available in private messages.");
		return;
	}

	if (words.size() < 3)
	{
		sendPrivateMsg(server, replyTarget, "[Tell] Usage: tell <nick> <message>");
		return;
	}

	const std::string &targetNick = words[1];
	Client *target = server->findClientByNickName(targetNick);
	if (!target)
	{
		server->sendErrorMsg(sender, ERR_NOSUCHNICK, targetNick, "No such nick");
		return;
	}

	// botDmTracker(sender, target);
	sendPrivateMsg(server, targetNick, "Someone told you: " + words[2]);
	sendPrivateMsg(server, replyTarget, "[Tell] Sent anonymously to " + targetNick + ".");
}

static int getRandomNumber(int max)
{
	static bool seeded = false;

	if (!seeded)
	{
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		seeded = true;
	}
	return std::rand() % max + 1;
}

void Bot::handleRollCommand(Server *server, const std::string &replyTarget,
                            const std::vector<std::string> &words)
{
	int sides = 6;

	if (words.size() >= 2)
	{
		std::istringstream iss(words[1]);
		if (!(iss >> sides) || sides <= 0)
		{
			sendPrivateMsg(server, replyTarget, "[Roll] Usage: roll [sides]");
			return;
		}
	}

	std::string result = "[Roll] Rolling a " + Utils::toString(sides) + "-sided die... " +
						Utils::toString(getRandomNumber(sides)) + "!";
	sendPrivateMsg(server, replyTarget, result);
}
