#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    try
    {
        Bureaucrat hector("Hector", 1);
        ShrubberyCreationForm sh("home");
        RobotomyRequestForm rr("Bender");
        PresidentialPardonForm pp("Alice");

        std::cout << sh << std::endl;
        hector.signForm(sh);
        hector.signForm(rr);
        hector.signForm(pp);

        hector.executeForm(sh);
        hector.executeForm(rr);
        hector.executeForm(pp);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
