# include "Form.hpp"

Form::Form(void) : _name("Nameless"), _signature(false),
                    _gradeToSign(1), _gradeToExec(1) {}

Form::Form(const Form &src) : _name(src._name), _signature(false),
                             _gradeToSign(src._gradeToSign), _gradeToExec(src._gradeToExec) {}

Form::Form(const std::string name, const int gts, const int gte) : _name(name), _signature(false),
                           _gradeToSign(gts), _gradeToExec(gte)
{
    if (_gradeToSign > 150 || _gradeToExec > 150)
        throw Form::GradeTooLowException();
    if (_gradeToSign < 1 || _gradeToExec < 1)
        throw Form::GradeTooHighException();
}

Form    &Form::operator=(const Form &src) {
    if (this == &src)
        return (*this);
    this->_signature = src._signature;
    return (*this);
}

Form::~Form() {}

std::ostream &operator<<(std::ostream &o, Form &src)
{
    o << CYAN << "+++++++++++++++++++++++++++++++++++++++++++++++++++\n" << RESET;
    o << PURPLE << "\t" << src.getName() << CYAN << " Form Info:\n" << RESET;
    o << YELLOW << "\t\tGrade to sign--------> " << CYAN << src.getGradeToSign() << std::endl << RESET;
    o << YELLOW << "\t\tGrade to execute-----> " << CYAN << src.getGradeToExec() << std::endl << RESET;

    if (src.getSignature())
        o << YELLOW << "\tStatus---------------> " << GREEN << "Signed." << std::endl << RESET;
    else
        o << YELLOW << "\tStatus---------------> " << RED << "Not Signed." << std::endl << RESET;

    o << CYAN << "+++++++++++++++++++++++++++++++++++++++++++++++++++\n" << RESET;
    return (o);
}

const std::string &Form::getName() const {
    return (_name);
}

bool Form::getSignature() const {
    return (_signature);
}

int Form::getGradeToSign() const {
    return (_gradeToSign);
}

int Form::getGradeToExec() const {
    return (_gradeToExec);
}

void Form::beSigned(Bureaucrat &bureaucrat)
{
    if (_signature)
        throw Form::FormPrevSignedException();
    if (bureaucrat.getGrade() <= _gradeToSign)
         _signature = true;
    else
        throw Form::GradeTooLowException();
}

const char *Form::GradeTooHighException::what() const throw()
{
    return ("Grade too high...");
}

const char *Form::GradeTooLowException::what() const throw()
{
    return ("Grade too low...");
}

const char *Form::FormPrevSignedException::what() const throw()
{
    return ("Form was already signed");
}