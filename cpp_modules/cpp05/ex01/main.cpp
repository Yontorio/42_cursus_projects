#include <iostream>

#include "Form.hpp"
#include "Bureaucrat.hpp"

int main()
{
    std::cout << "=== Testing Exercice 01 ===\n";

    std::cout << "\n1. Create valid Form and valid Bureaucrat:\n";
    try
    {
        Form f("TopSecret", 5, 10);
        Bureaucrat b("Alice", 3);
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << "After signing: " << f << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n2. Signing with too low grade bureaucrat:\n";
    try
    {
        Form f("Confidential", 10, 20);
        Bureaucrat low("Bob", 50);
        std::cout << f << std::endl;
        low.signForm(f); // should throw Form::GradeTooLowException
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n3. Attempt to sign an already signed form:\n";
    try
    {
        Form f("Permit", 100, 120);
        Bureaucrat signer("Carlos", 50);
        signer.signForm(f);
        std::cout << "Signed once: " << f << std::endl;
        signer.signForm(f); // should throw Form::AlreadySignedException
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n4. Create form with invalid grades:\n";
    try
    {
        Form bad("BadForm", 0, 200); // gradeSign too high, gradeExec too low
    }                                // should throw Form::GradeTooHighException only
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Tests completed ===\n";
    return 0;
}
