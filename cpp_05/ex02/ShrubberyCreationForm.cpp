# include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) : AForm("none", 145, 137), _target("none") {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &src) : AForm(src){}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("RobotomyRequestForm", 145, 137),
                                                                             _target(target){}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm &src)
{
    if (this == &src)
        return (src);
    AForm::operator=(src);
    return(*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm(){}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {

    this->checkRequirements(executor);
    
    std::string fileName = _target + "_shrubbery";
    std::ofstream o(fileName.c_str());

    o << "    /\\     \n";
    o << "   // \\     \n";
    o << "  ///  \\     \n";
    o << " ////   \\     \n";
    o << "/////    \\     \n";
    o << "  ||||||     \n";
    o << "  ||||||     \n";
    o << "  ||||||     \n";
    o << "  ||||||     \n";


}