#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>

class Utils
{
  private:
	Utils();
	Utils(Utils const &other);
	Utils &operator=(Utils const &other);
	~Utils();

  public:
	static std::vector<std::string> &splitString(std::vector<std::string> &tokens,
																	 const std::string &str,
																	 char delimiter);
	static void stringToUpper(std::string &str);
	static std::string ltrimSpaces(const std::string &s);
	static std::string toLower(std::string value);
	static std::string formatDuration(long seconds);
	static std::string getCurrentDateTime();

	template <typename T>
	static std::string toString(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}


};

#endif
