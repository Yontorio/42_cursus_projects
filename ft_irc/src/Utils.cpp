#include "Utils.hpp"

#include <cctype>
#include <sstream>
#include <ctime>

std::vector<std::string> &Utils::splitString(std::vector<std::string> &tokens,
																	const std::string &str,
																	char delimiter)
{
	std::string		token;
	std::istringstream tokenStream(str);

	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void Utils::stringToUpper(std::string &str)
{
	for (std::string::size_type i = 0; i < str.size(); ++i)
	{
		str[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(str[i])));
	}
}

std::string Utils::toLower(std::string value)
{
	for (std::string::iterator it = value.begin(); it != value.end(); ++it)
		*it = static_cast<char>(std::tolower(static_cast<unsigned char>(*it)));
	return value;
}

std::string Utils::ltrimSpaces(const std::string &s)
{
	std::string::size_type i = 0;
	while (i < s.size() && s[i] == ' ')
		++i;
	return s.substr(i);
}

std::string Utils::formatDuration(long seconds)
{
	if (seconds < 0)
		seconds = 0;
	if (seconds >= 3600)
	{
		return toString(seconds / 3600) + "h " + toString((seconds % 3600) / 60) + "m " + toString(seconds % 60) + "s";
	}
	if (seconds >= 60)
	{
		return toString(seconds / 60) + "m " + toString(seconds % 60) + "s";
	}
	return toString(seconds) + "s";
}

std::string Utils::getCurrentDateTime()
{
	std::time_t now = std::time(NULL);
	std::tm *tm = std::localtime(&now);
	char buf[64];

	if (!tm)
		return "(time unavailable)";
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
	return std::string(buf);
}

