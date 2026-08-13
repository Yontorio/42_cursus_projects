#include "Intern.hpp"

int main()
{
    Intern intern;
    Bureaucrat boss("Boss", 1);
    AForm* forms[4] =
    {
        intern.makeForm("robotomy request", "Bender"),
        intern.makeForm("shrubbery creation", "home"),
        intern.makeForm("presidential pardon", "Arthur Dent"),
        intern.makeForm("unknown form", "Nobody")
    };

    for (int i = 0; i < 4; ++i)
    {
        if (forms[i])
        {
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
            delete forms[i];
        }
    }
    return (0);
}
