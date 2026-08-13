#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() : _name("Default"), _grade(GradeRange::LOWEST) {}

int Bureaucrat::validateGrade(int grade)
{
    if (grade < GradeRange::HIGHEST)
        throw GradeTooHighException();
    if (grade > GradeRange::LOWEST)
        throw GradeTooLowException();
    return (grade);
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) :
                    _name(name), _grade(validateGrade(grade)) {}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : 
                    _name(other._name), _grade(other._grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    if (this != &other) { this->_grade = other._grade; }
    return (*this);
}

const   std::string &Bureaucrat::getName()  const { return _name; }
int     Bureaucrat::getGrade()              const { return _grade; }

void Bureaucrat::incrementGrade()
{
    if (_grade - 1 < GradeRange::HIGHEST) throw GradeTooHighException();
    --_grade;
}

void Bureaucrat::decrementGrade()
{
    if (_grade + 1 > GradeRange::LOWEST) throw GradeTooLowException();
    ++_grade;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{ return "Bureaucrat::GradeTooHighException"; }

const char *Bureaucrat::GradeTooLowException::what() const throw()
{ return "Bureaucrat::GradeTooLowException"; }

std::ostream &operator<<(std::ostream &os, const Bureaucrat &b)
{ return (os << b.getName() << ", bureaucrat grade " << b.getGrade()); }

void Bureaucrat::signForm(AForm &form) const
{
    try
    {
        form.beSigned(*this);
        std::cout << this->getName() << " signed "
                  << form.getName() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << this->getName() << " couldn't sign " << form.getName()
                  << " because " << e.what() << "." << std::endl;
    }
}

void Bureaucrat::executeForm(AForm const &form) const
{
    try
    {
        form.execute(*this);
        std::cout << this->getName() << " executed "
                  << form.getName() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << this->getName() << " couldn't execute " << form.getName()
                  << " because " << e.what() << "." << std::endl;
    }
}
