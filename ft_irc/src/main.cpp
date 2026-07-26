#include "Server.hpp"
#include <string>
#include <cstdlib>

int	main(int ac, char **av)
{
	int			port;
	std::string password;

	if (ac != 3)
	{
		std::cerr << "Usage: irserv port passowrd" << std::endl;
		return (1);
	}
	try
	{
		port = atoi(av[1]);
		password = av[2];
		Server s(port, password);
		s.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	
	return (0);
}