#include "PhoneBook.hpp"

int main()
{
    PhoneBook pb;
    std::string cmd;

    while (true)
    {
        std::cout << "Command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, cmd) || cmd == "EXIT")
        {
            break;
        }
        else if (cmd == "SEARCH")
        {
            pb.search();
        }
        else if (cmd == "ADD")
        {
            pb.add();
        }
    }
    return (0);
}
