#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
    private:
        std::string _target;

    public:
        PresidentialPardonForm();
        PresidentialPardonForm(const std::string &target);
        PresidentialPardonForm(const PresidentialPardonForm &other);
        ~PresidentialPardonForm();

        PresidentialPardonForm &operator=(const PresidentialPardonForm &other);

        virtual void execute(const Bureaucrat &executor) const;
};

#endif
