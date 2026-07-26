#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <vector>

class Server;
class Client;
class Channel;

class Bot
{
  private:
	Bot();
	Bot(const Bot &);
	Bot &operator=(const Bot &);
	~Bot();

	static std::string buildPrefix();
	static bool isChannelTarget(const std::string &target);
	static void sendPrivateMsg(Server *server, const std::string &target, const std::string &text);
	static void replyMultiLine(Server *server, const std::string &replyTarget, const std::string &text);
	static void handleCommand(Server *server, Client *sender, const std::string &replyTarget,
	                          const std::string &commandText);
	static void handleHelpCommand(Server *server, const std::string &replyTarget);
	static void handleTimeCommand(Server *server, const std::string &replyTarget);
	static void handleStatsCommand(Server *server, const std::string &replyTarget);
	static void handleInBoxCommand(Server *server, Client *sender, const std::string &replyTarget);
	static void handleTellCommand(Server *server, Client *sender, const std::string &replyTarget,
	                              const std::vector<std::string> &words);
	static void handleRollCommand(Server *server, const std::string &replyTarget,
	                              const std::vector<std::string> &words);
	static void handlePollCommand(Server *server, Client *sender, const std::string &replyTarget,
	                              const std::vector<std::string> &words);
	static void handlePollStartCommand(Server *server, Client *sender, const std::string &replyTarget,
	                                   const std::vector<std::string> &words);
	static void handlePollEndCommand(Server *server, const std::string &replyTarget);
	static void handlePollVoteCommand(Server *server, Client *sender, const std::string &replyTarget,
	                                  const std::string &vote);
	static void sendPollStatus(Server *server, const std::string &replyTarget,
	                           const struct PollState &poll, bool showVotes);

  public:
	static const std::string &getNick();

	static void botOnRegisterMsg(Server *server, Client *client);
	static void botOnJoinMsg(Server *server, Client *client, Channel *channel);
	static void botOnPrivateMsg(Server *server, Client *sender, const std::string &text);
	static void botDmTracker(Client *sender, Client *target);
	static void botChannelCommand(Server *server, Client *sender, Channel *channel,
	                              const std::string &text);
};

#endif
