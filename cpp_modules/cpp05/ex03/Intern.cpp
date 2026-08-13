#include "Intern.hpp"

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern::~Intern() {}

Intern& Intern::operator=(const Intern&) { return (*this); }

static AForm* newRRForm(const std::string& target)
{ return (new RobotomyRequestForm(target)); }

static AForm* newSCForm(const std::string& target)
{ return (new ShrubberyCreationForm(target)); }
static AForm* newPPForm(const std::string& target)
{ return (new PresidentialPardonForm(target)); }

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
    FormCreator forms[3] = { newRRForm, newSCForm, newPPForm };

    const std::string formNames[3] =
        { "robotomy request", "shrubbery creation", "presidential pardon" };

    for (int i = 0; i < 3; ++i)
    {
        if (formName == formNames[i])
        {
            std::cout << "Intern creates " << formName << std::endl;
            return (forms[i](target));
        }
    }
    std::cout << "Intern: Error, form name '" << formName << "' does not exist." << std::endl;
    return (NULL);
} 
