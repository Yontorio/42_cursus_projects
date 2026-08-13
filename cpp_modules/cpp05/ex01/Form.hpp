#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

std::ostream &operator<<(std::ostream &os, const Form &f);

class Form
{
    private:
        const std::string _name;
        bool              _isSigned;
        const int         _gradeSign;
        const int         _gradeExec;
    
    protected:
        int validateGrade(int grade);

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
        class AlreadySignedException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        Form();
        Form(const std::string &name, int gradeSign, int gradeExec);
        Form(const Form &other);
        ~Form();

        Form &operator=(const Form &other);

        const std::string   &getName() const;
        bool                isSigned() const;
        int                 getGradeSign() const;
        int                 getGradeExec() const;
        
        void beSigned(const Bureaucrat &b);
};

#endif
