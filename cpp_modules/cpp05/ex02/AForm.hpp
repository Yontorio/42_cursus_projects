#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"

std::ostream &operator<<(std::ostream &os, const AForm &f);

class AForm
{
    private:
        const std::string   _name;
        bool                _isSigned;
        const int           _gradeSign;
        const int           _gradeExec;

    protected:
        int     validateGrade(int grade);
        void    isFormExecutable(const Bureaucrat &executor) const;
    
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
        class NotSignedException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        AForm();
        AForm(const std::string &name, int gradeSign, int gradeExec);
        AForm(const AForm &other);
        virtual ~AForm();

        AForm &operator=(const AForm &other);

        const std::string   &getName() const;
        bool                isSigned() const;
        int                 getGradeSign() const;
        int                 getGradeExec() const;

        void            beSigned(const Bureaucrat &b);
        virtual void    execute(const Bureaucrat &executor) const = 0;
};

#endif
