#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook() : _count(0), _next(0) {}

std::string PhoneBook::format(const std::string& s) {
    if (s.length() > 10)
        return s.substr(0, 9) + ".";
    return s;
}

void PhoneBook::add() {
    std::string fn, ln, nn, pn, ds;

    std::cout << "First name: "; std::getline(std::cin, fn);
    std::cout << "Last name: "; std::getline(std::cin, ln);
    std::cout << "Nickname: "; std::getline(std::cin, nn);
    std::cout << "Phone number: "; std::getline(std::cin, pn);
    std::cout << "Darkest secret: "; std::getline(std::cin, ds);

    if (fn.empty() || ln.empty() || nn.empty() || pn.empty() || ds.empty()) {
        std::cout << "Empty field not allowed\n";
        return;
    }

    _contacts[_next].set(fn, ln, nn, pn, ds);
    _next = (_next + 1) % MAX;
    if (_count < MAX)
        _count++;
}

void PhoneBook::search() const {
    if (_count == 0) {
        std::cout << "PhoneBook is empty\n";
        return;
    }
    std::cout << std::setw(10) << std::right << "Index" << "|"
              << std::setw(10) << std::right << "First Name" << "|"
              << std::setw(10) << std::right << "Last Name" << "|"
              << std::setw(10) << std::right << "Nickname" << "\n";
    for (int i = 0; i < _count; i++) {
        const Contact &c = _contacts[i];
        std::cout << std::setw(10) << std::right << i << "|"
                  << std::setw(10) << std::right << format(c.firstName()) << "|"
                  << std::setw(10) << std::right << format(c.lastName()) << "|"
                  << std::setw(10) << std::right << format(c.nickname()) << "\n";
    }

    std::cout << "Choose index: ";
    std::string in;
    std::getline(std::cin, in);
    if (in.size() != 1 || in[0] < '0' || in[0] > '7')
    {
        std::cout << "Invalid index" << std::endl;
        return;
    }
    showContact(in[0] - '0');
}

void PhoneBook::showContact(int i) const
{
    if (i >= _count)
    {
        std::cout << "Index not found" << std::endl;
        return;
    }
    std::cout << "First name: " << _contacts[i].firstName() << "\n";
    std::cout << "Last name: " << _contacts[i].lastName() << "\n";
    std::cout << "Nickname: " << _contacts[i].nickname() << "\n";
    std::cout << "Phone number: " << _contacts[i].phone() << "\n";
    std::cout << "Darkest secret: " << _contacts[i].secret() << "\n";
}
