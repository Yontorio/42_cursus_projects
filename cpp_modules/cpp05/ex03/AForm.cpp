#include "AForm.hpp"

AForm::AForm() : 
        _name("Default"),
        _isSigned(false),
        _gradeSign(GradeRange::LOWEST),
        _gradeExec(GradeRange::LOWEST) {}

int AForm::validateGrade(int grade)
{
    if (grade < GradeRange::HIGHEST)
        throw GradeTooHighException();
    if (grade > GradeRange::LOWEST)
        throw GradeTooLowException();
    return (grade);
}

AForm::AForm(const std::string &name, int gradeSign, int gradeExec) : 
        _name(name),
        _isSigned(false),
        _gradeSign(validateGrade(gradeSign)),
        _gradeExec(validateGrade(gradeExec)) {}

AForm::AForm(const AForm &other) : 
        _name(other._name),
        _isSigned(other._isSigned),
        _gradeSign(other._gradeSign),
        _gradeExec(other._gradeExec) {}

AForm::~AForm() {}

AForm &AForm::operator=(const AForm &other)
{
    if (this != &other) { this->_isSigned = other._isSigned; }
    return (*this);
}

const   std::string &AForm::getName() const  { return _name; }
bool    AForm::isSigned()             const  { return _isSigned; }
int     AForm::getGradeSign()         const  { return _gradeSign; }
int     AForm::getGradeExec()         const  { return _gradeExec; }

void AForm::beSigned(const Bureaucrat &b)
{
    if (_isSigned)
        throw AlreadySignedException();
    if (b.getGrade() > _gradeSign)
        throw GradeTooLowException();
    _isSigned = true;
}

void AForm::isFormExecutable(const Bureaucrat &executor) const
{
    if (!_isSigned)
        throw NotSignedException();
    if (executor.getGrade() > _gradeExec)
        throw GradeTooLowException();
}

const char *AForm::GradeTooHighException::what() const throw()
{ return "AForm::GradeTooHighException"; }

const char *AForm::GradeTooLowException::what() const throw()
{ return "AForm::GradeTooLowException"; }

const char *AForm::AlreadySignedException::what() const throw()
{ return "AForm::AlreadySignedException"; }

const char *AForm::NotSignedException::what() const throw()
{ return "AForm::NotSignedException"; }

std::ostream &operator<<(std::ostream &os, const AForm &f)
{
    return
    (   
        os  << "Form \"" << f.getName() << "\""
            << ", state: "<< (f.isSigned() ? "signed" : "not signed")
            << ", grade \"" << f.getGradeSign() << "\" required to sign"
            << ", grade \"" << f.getGradeExec() << "\" required to execute."
    );
}
