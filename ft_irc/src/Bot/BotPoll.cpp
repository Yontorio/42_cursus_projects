#include "Bot.hpp"

#include "Client.hpp"
#include "Server.hpp"
#include "Utils.hpp"

#include <ctime>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct PollState
{
	std::string question;
	std::time_t startedAt;
	std::map<std::string, std::string> votes;
};

static std::map<std::string, PollState> pollsByChannel;

static bool hasPoll(const std::string &replyTarget)
{
	return pollsByChannel.find(replyTarget) != pollsByChannel.end();
}

static std::string extractPollQuestion(const std::vector<std::string> &words)
{
	if (words.size() < 3)
		return "";
	return words[2];
}

static int countVotes(const PollState &poll, const std::string &vote)
{
	int count = 0;

	for (std::map<std::string, std::string>::const_iterator it = poll.votes.begin();
	     it != poll.votes.end(); ++it)
	{
		if (it->second == vote)
			++count;
	}
	return count;
}

void Bot::sendPollStatus(Server *server, const std::string &replyTarget,
                         const PollState &poll, bool showVotes)
{
	std::string msg;
	long elapsed = static_cast<long>(std::time(NULL) - poll.startedAt);

	msg = "[Poll] Question: " + poll.question + "\n";
	msg += "[Poll] Running for: " + Utils::formatDuration(elapsed) +
	       " | Total votes: " + Utils::toString(poll.votes.size());
	if (showVotes)
	{
		msg += "\n[Poll] Current results: " +
			   Utils::toString(countVotes(poll, "yes")) + " yes, " +
			   Utils::toString(countVotes(poll, "no")) + " no";
	}
	replyMultiLine(server, replyTarget, msg);
}

static void startPoll(const std::string &replyTarget, const std::string &question)
{
	PollState poll;

	poll.question = question;
	poll.startedAt = std::time(NULL);
	pollsByChannel[replyTarget] = poll;
}

void Bot::handlePollStartCommand(Server *server, Client *sender, const std::string &replyTarget,
                                 const std::vector<std::string> &words)
{
	std::string question = extractPollQuestion(words);
	if (hasPoll(replyTarget))
	{
		sendPrivateMsg(server, replyTarget,
			"[Poll] There is already an ongoing poll. Use 'poll end' first to start a new one.");
		return;
	}
	if (question.empty())
	{
		sendPrivateMsg(server, replyTarget, "[Poll] Usage: poll start <question>");
		return;
	}
	startPoll(replyTarget, question);
	sendPrivateMsg(server, replyTarget,
	               "[Poll] " + sender->getNickname() + " started: " + question);
	sendPrivateMsg(server, replyTarget, "[Poll] Vote with: poll yes / poll no");
}

void Bot::handlePollEndCommand(Server *server, const std::string &replyTarget)
{
	sendPrivateMsg(server, replyTarget, "[Poll] Ended. Final result:");
	sendPollStatus(server, replyTarget, pollsByChannel[replyTarget], true);
	pollsByChannel.erase(replyTarget);
}

void Bot::handlePollVoteCommand(Server *server, Client *sender, const std::string &replyTarget,
                                const std::string &vote)
{
	pollsByChannel[replyTarget].votes[sender->getNickname()] = vote;
	sendPrivateMsg(server, replyTarget, "[Poll] " + sender->getNickname() + " voted " + vote + ".");
}

void Bot::handlePollCommand(Server *server, Client *sender, const std::string &replyTarget,
                            const std::vector<std::string> &words)
{
	std::string action;

	if (!isChannelTarget(replyTarget))
	{
		return sendPrivateMsg(server, replyTarget, "[Poll] This command is only available in channels.");
	}
	action = words.size() >= 2 ? Utils::toLower(words[1]) : "";
	if (action == "start")
	{
		return handlePollStartCommand(server, sender, replyTarget, words);
	}
	if (!hasPoll(replyTarget))
	{
		return sendPrivateMsg(server, replyTarget, "[Poll] There is no active poll right now.");
	}
	if (action.empty())
	{
		return sendPollStatus(server, replyTarget, pollsByChannel[replyTarget], false);
	}
	if (action == "result")
	{
		return sendPollStatus(server, replyTarget, pollsByChannel[replyTarget], true);
	}
	if (action == "end")
	{
		return handlePollEndCommand(server, replyTarget);
	}
	if (action == "yes" || action == "no")
	{
		return handlePollVoteCommand(server, sender, replyTarget, action);
	}
	sendPrivateMsg(server, replyTarget, "[Poll] Usage: poll start <question> | poll yes | poll no | poll result | poll end");
}
