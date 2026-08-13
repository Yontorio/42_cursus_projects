#include "Form.hpp"

Form::Form() : 
        _name("Default"),
        _isSigned(false),
        _gradeSign(GradeRange::LOWEST),
        _gradeExec(GradeRange::LOWEST) {}

int Form::validateGrade(int grade)
{
    if (grade < GradeRange::HIGHEST)
        throw GradeTooHighException();
    if (grade > GradeRange::LOWEST)
        throw GradeTooLowException();
    return (grade);
}

Form::Form(const std::string &name, int gradeSign, int gradeExec) : 
        _name(name),
        _isSigned(false),
        _gradeSign(validateGrade(gradeSign)),
        _gradeExec(validateGrade(gradeExec)) {}

Form::Form(const Form &other) : 
        _name(other._name),
        _isSigned(other._isSigned),
        _gradeSign(other._gradeSign),
        _gradeExec(other._gradeExec) {}

Form::~Form() {}

Form &Form::operator=(const Form &other)
{
    if (this != &other) { this->_isSigned = other._isSigned; }
    return (*this);
}

const   std::string &Form::getName() const  { return _name; }
bool    Form::isSigned()             const  { return _isSigned; }
int     Form::getGradeSign()         const  { return _gradeSign; }
int     Form::getGradeExec()         const  { return _gradeExec; }

void Form::beSigned(const Bureaucrat &b)
{
    if (_isSigned)
        throw AlreadySignedException();
    if (b.getGrade() > _gradeSign)
        throw GradeTooLowException();
    _isSigned = true;
}

const char *Form::GradeTooHighException::what() const throw()
{ return "Form::GradeTooHighException"; }

const char *Form::GradeTooLowException::what() const throw()
{ return "Form::GradeTooLowException"; }

const char *Form::AlreadySignedException::what() const throw()
{ return "Form::AlreadySignedException"; }

std::ostream &operator<<(std::ostream &os, const Form &f)
{
    return
    (   
        os  << "Form \"" << f.getName() << "\""
            << ", state: "<< (f.isSigned() ? "signed" : "not signed")
            << ", grade \"" << f.getGradeSign() << "\" required to sign"
            << ", grade \"" << f.getGradeExec() << "\" required to execute."
    );
}
