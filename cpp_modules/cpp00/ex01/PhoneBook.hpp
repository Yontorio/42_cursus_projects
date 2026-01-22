#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

class PhoneBook {
public:
    PhoneBook();

    void add();
    void search() const;

private:
    static const int MAX = 8;

    Contact _contacts[MAX];
    int _count;
    int _next;

    static std::string format(const std::string& s);
    void showContact(int index) const;
};

#endif
