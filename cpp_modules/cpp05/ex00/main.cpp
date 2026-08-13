#include "Bureaucrat.hpp"

int main()
{
    std::cout << "=== Testing Exercice 00 ===\n";

    std::cout << "\n1. Testing default constructor:\n";
    Bureaucrat def;
    std::cout << def << std::endl;

    std::cout << "\n2. Testing parameterized constructor with valid & invalid grades:\n";
    std::cout << "valid grade:\n";
    Bureaucrat a("Nikola", 1);
    std::cout << a << std::endl;

    std::cout << "invalid grade:\n";
    try 
    {
        Bureaucrat c("Albert", 151); // Should throw
        std::cout << c << std::endl;
    } 
    catch (const std::exception &e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n3. Testing copy constructor:\n";
    Bureaucrat copy_a(a);
    std::cout << "Original: " << a << std::endl;
    std::cout << "Copy: " << copy_a << std::endl;

    std::cout << "\n4. Testing assignment operator:\n";
    Bureaucrat assign("Assign", 100);
    assign = a;
    std::cout << "Assigned: " << assign << std::endl;

    std::cout << "\n5. Testing incrementGrade:\n";
    {
        int startGrade = GradeRange::LOWEST;
        Bureaucrat inc("Increment", startGrade);
        std::cout << "Starting at: " << inc << std::endl;
        try
        {        
            while (true)
            {
                inc.incrementGrade();
                // std::cout << "After increment: " << inc << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

    }

    std::cout << "\n6. Testing decrementGrade:\n";
    try
    {
        Bureaucrat dec("Decrement", 149);
        std::cout << "Before: " << dec << std::endl;
        dec.decrementGrade();
        std::cout << "After decrement: " << dec << std::endl;
        dec.decrementGrade(); // Should throw
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n7. Testing invalid grades in constructor:\n";
    try
    {   
        Bureaucrat invalid_high("InvalidHigh", 0); // Should throw
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat invalid_low("InvalidLow", 151); // Should throw
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== All tests completed ===\n";
    return (0);
}
