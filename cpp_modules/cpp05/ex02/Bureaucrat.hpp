#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

class Bureaucrat;
class AForm;

namespace GradeRange { enum { HIGHEST = 1, LOWEST = 150 }; };

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

class Bureaucrat
{
    private:
        const std::string _name;
        int               _grade;

        static int validateGrade(int grade);

    public:
        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
        
        Bureaucrat();
        Bureaucrat(const std::string &name, int grade);
        Bureaucrat(const Bureaucrat &other);
        ~Bureaucrat();

        Bureaucrat &operator=(const Bureaucrat &other);

        const std::string   &getName() const;
        int                 getGrade() const;

        void incrementGrade();
        void decrementGrade();
        void signForm(AForm &form) const;
        void executeForm(AForm const &form) const;
};

#endif
