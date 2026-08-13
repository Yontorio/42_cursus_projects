#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequest", 72, 45), _target("Default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequest", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), _target(other._target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        _target = other._target;
    }
    return (*this);
}

static void seedRandOneTime()
{
    static bool seeded = false;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
    isFormExecutable(executor);
    seedRandOneTime();
    std::cout << "* Bzzzt... Vrrrrr... Pshhh... *" << std::endl;
    if (rand() % 2)
        std::cout << _target << " has been robotomized successfully." << std::endl;
    else
        std::cout << "Robotomy failed on " << _target << std::endl;
}
