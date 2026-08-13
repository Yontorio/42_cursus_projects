#ifndef INTERN_HPP
#define INTERN_HPP

#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

typedef AForm* (*FormCreator)(const std::string&);

class Intern
{
    public:
        Intern();
        Intern(const Intern& other);
        ~Intern();

        Intern& operator=(const Intern& other);

        AForm* makeForm(const std::string& formName, const std::string& target) const;
};

#endif
