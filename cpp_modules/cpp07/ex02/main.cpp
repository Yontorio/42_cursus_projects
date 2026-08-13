#include "Array.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//

    //MY TESTS
    try
    {
        std::cout << "\n===== Default Constructor =====\n";
        Array<int> empty;
        std::cout << "Size = " << empty.size() << std::endl;
        std::cout << "\n===== Value Initialization =====\n";
        Array<int> values(5);
        for (unsigned int i = 0; i < values.size(); ++i)
            std::cout << values[i] << " ";
        std::cout << std::endl;
        std::cout << "\n===== Deep Copy =====\n";
        Array<int> a(3);
        a[0] = 11;
        a[1] = 22;
        a[2] = 33;
        Array<int> b = a;
        b[0] = 44;
        std::cout << "a[0] = " << a[0] << std::endl;
        std::cout << "b[0] = " << b[0] << std::endl;
        std::cout << "\n===== Const Array =====\n";
        const Array<int> constArray(numbers);
        std::cout << constArray[0] << std::endl;
        std::cout << "\n===== Strings =====\n";
        Array<std::string> words(3);
        words[0] = "CPP";
        words[1] = "07";
        words[2] = "OUT";
        for (unsigned int i = 0; i < words.size(); ++i)
            std::cout << words[i] << " ";
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
