#ifndef IRCMESSAGETOKENIZER_HPP
# define IRCMESSAGETOKENIZER_HPP

#include <string>
#include <vector>

struct ParsedMessage
{
	std::string              command;
	std::vector<std::string> args;
};

class IrcMessageTokenizer
{
public:
	static void parse(const std::string& line, ParsedMessage& out);

private:
	static bool isAtCRLF(const std::string& msg, std::size_t i);
	static void skipSpaces(const std::string& msg, std::size_t& i);
	static std::string extractToken(const std::string& msg, std::size_t& i);
	static std::string extractTrailing(const std::string& msg, std::size_t& i);
	static void tokenizeParams(const std::string& msg, std::vector<std::string>& tokens, std::size_t& endPos);
};

#endif
