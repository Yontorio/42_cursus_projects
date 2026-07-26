#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <set>
#include <string>
#include <utility>
#include <vector>

class Channel;
class Server;

class Client
{
	public:
	static const size_t MAX_NICK_LENGTH = 16;

	private:
	const int fd;
	const std::string ip;
	std::string inputBuffer;
	std::string nickname;
	std::string username;
	std::string realname;
	std::string password;
	std::string outputBuffer;
	bool authenticated;
	bool registered;
	
	std::set<Channel *> invitedTo;
	std::set<Channel *> channels;
	Client (Client const &other);
	Client &operator=(Client const &other);
	Client();

	public:
	typedef std::set<Channel *>::iterator channelIterator;

	Client(int fd, const std::string &ip);
	~Client();

	int getFd() const;
	const std::string &getIp() const;
	size_t getInputBufferSize() const;
	const std::string &getNickname() const;
	const std::string &getUsername() const;
	const std::string &getRealname() const;
	const std::string &getPassword() const;
	bool hasNickname() const;
	bool hasRealname() const;
	const std::string &getOutputBuffer() const;
	bool hasPendingOutput() const;
	bool isAuthenticated() const;
	bool isRegistered() const;
	const std::set<Channel *> &getChannels() const;
	const std::set<Channel *> &getInvitedChannels() const;
	channelIterator beginChannels();
	channelIterator endChannels();
	std::string getPrefix() const;

	void setNickname(const std::string &nickname);
	void setUsername(const std::string &username);
	void setRealname(const std::string &realname);
	void setPassword(const std::string &password);
	void setAuthenticated(bool state);
	void setRegistered(bool state);

	void addToInputBuffer(char const *data, size_t len);
	void queueOutput(const std::string &data);
	void consumeOutput(size_t len);
	void clearInputBuffer();
	std::string extractLine();

	void joinChannel(Channel *channel);
	void leaveChannel(Channel *channel);
	void addChannelToInviteList(Channel *channel);
	void removeChannelFromInviteList(Channel *channel);
	void removeFromAllChannelInviteLists();
	bool isInvitedTo(Channel *channel) const;
};

#endif
