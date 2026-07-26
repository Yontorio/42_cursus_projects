#include "IrcMessageTokenizer.hpp"
#include <cctype>

bool IrcMessageTokenizer::isAtCRLF(const std::string& msg, std::size_t i)
{
	return i < msg.size() && msg[i] == '\r' && i + 1 < msg.size() && msg[i + 1] == '\n';
}

void IrcMessageTokenizer::skipSpaces(const std::string& msg, std::size_t& i)
{
	while (i < msg.size() && msg[i] == ' ' && !isAtCRLF(msg, i))
		i++;
}

std::string IrcMessageTokenizer::extractToken(const std::string& msg, std::size_t& i)
{
	std::size_t start = i;
	while (i < msg.size() && msg[i] != ' ' && !isAtCRLF(msg, i))
		i++;
	return msg.substr(start, i - start);
}

std::string IrcMessageTokenizer::extractTrailing(const std::string& msg, std::size_t& i)
{
	i++;
	std::size_t start = i;
	while (i < msg.size() && !isAtCRLF(msg, i))
		i++;
	return msg.substr(start, i - start);
}

void IrcMessageTokenizer::tokenizeParams(const std::string& msg, std::vector<std::string>& tokens, std::size_t& endPos)
{
	std::size_t i = 0;

	skipSpaces(msg, i);
	while (i < msg.size() && !isAtCRLF(msg, i))
	{
		if (msg[i] == ':')
		{
			tokens.push_back(extractTrailing(msg, i));
			break;
		}
		else
		{
			tokens.push_back(extractToken(msg, i));
			skipSpaces(msg, i);
		}
	}
	endPos = i;
}

void IrcMessageTokenizer::parse(const std::string& line, ParsedMessage& out)
{
	std::size_t i = 0;
	std::size_t endPos = 0;

	skipSpaces(line, i);
	out.command = extractToken(line, i);
	if (out.command.empty())
		return;
	tokenizeParams(line.substr(i), out.args, endPos);
	if (!isAtCRLF(line, i + endPos))
	{
		out.command.clear();
		out.args.clear();
	}
}
