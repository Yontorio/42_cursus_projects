#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreation", 145, 137), _target("Default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreation", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        _target = other._target;
    }
    return (*this);
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
    isFormExecutable(executor);

    std::string fileName = _target + "_shrubbery";
    std::ofstream ofs(fileName.c_str());
    if (!ofs)
    {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }

    const std::string tree[] =
    {
        "                   *     ",
        "            A            ",
        "      *    d$b           ",
        "          d$$@b *        ",
        "         d*$$$ib     *   ",
        "   *   .d$$$*@$$b.       ",
        "     .d$$@$$$$*$$ib.     ",
        "       .d$$$*@$$b.       ",
        "     *.d$$$$@$$*$b.      ",
        "     .d$$$*@$$$$$$b.    *",
        "   .d$$@$$$$$i$$*$$$b.   ",
        "          #####       *  ",
        "   *      #####    *     ",
        "********* ##### *********",
        "*************************"
    };    
    int size = sizeof(tree) / sizeof(tree[0]);
    for (int r = 0; r < size; ++r)
    {
        for (int i = 3; i > 0; i--) ofs << tree[r];
        ofs << std::endl;
    }
    ofs.close();
}
