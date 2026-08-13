#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
    private:
        std::string _target;
        
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(const std::string &target);
        RobotomyRequestForm(const RobotomyRequestForm &other);
        ~RobotomyRequestForm();

        RobotomyRequestForm &operator=(const RobotomyRequestForm &other);

        virtual void execute(const Bureaucrat &executor) const;
};

#endif
