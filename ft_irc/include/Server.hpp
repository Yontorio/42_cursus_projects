#ifndef SERVER_HPP
#define SERVER_HPP

#include "CommandHandler.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

#include <cerrno>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <sys/epoll.h>
#include <algorithm>
#include <unistd.h>

class Client;

class Server
{
  private:
	const static std::string serverName;
	static const int MAX_EPOLL_EVENTS = 1024;
	const std::string password;
	const int port;
	int mainSocketFd;
	int epoll_fd;
	std::time_t startTime;
	std::map<int, Client *> clientsByFd;
	std::map<std::string, Channel *> channels;

	void acceptConnections();
	int receiveData(int fd);
	void setupSocket();
	void updatePollEvents(int fd);
	int flushOutput(Client *client);

	int executeCmds(int fd);
	void addClient(Client *client);
	int removeClient(int fd, const std::string &quitMsg = "Client exited");
	Client *findClientByFd(int fd);

	void handleReadyPollFd(const struct epoll_event &event);
  public:
	static const size_t MAX_MSG_LEN = 512;
	static const std::string &getServerName();

	bool hasPassword() const;
	bool isPasswordCorrect(const std::string &password) const;
	std::string getNamesList(Channel *channel);
	size_t getClientCount() const;
	size_t getChannelCount() const;
	std::string getUptimeString() const;
	std::string getChannelNamesString() const;

	Server(int port, const std::string &password);
	void sendData(Client *client, const std::string &message);
	void updatePollEvents(Client *client);
	~Server();
	Server(Server const &other);

	Client *findClientByNickName(const std::string &name);
	Channel *findChannel(const std::string &name);
	Channel *createChannel(const std::string &name);

	void changeClientNickname(Client *client, const std::string &newNick);
	void addChannel(Channel *channel);
	void removeChannel(Channel *channel);

	void sendData(int fd, const std::string &message);
	void sendReply(Client *client, const std::string &replyCode, const std::string &replyMsg);
	void sendErrorMsg(Client *client, const std::string &errCode, const std::string &target,
	                  const std::string &reason);
	void broadcastToChannel(Channel *channel, const std::string &msg, int excludeFd = -1);

	void run();
};

#endif
