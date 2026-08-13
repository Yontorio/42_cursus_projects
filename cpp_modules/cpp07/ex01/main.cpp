#include "iter.hpp"
#include <iostream>

void increment(int &x)
{
    x++;
}

void printInt(const int &x)
{
    std::cout << x << " ";
}

void printString(const std::string &s)
{
    std::cout << s << " ";
}

int main()
{
    std::cout << "===== Test 1 =====\n";

    int numbers[] = {1, 2, 3, 4, 5};

    iter(numbers, 5, increment);

    iter<const int>(numbers, 5, printInt);

    std::cout << "\n\n";



    std::cout << "===== Test 2 =====\n";

    const int constNumbers[] = {10, 20, 30};

    iter(constNumbers, 3, printInt);

    std::cout << "\n\n";



    std::cout << "===== Test 3 =====\n";

    const std::string words[] = {
        "CPP07",
        "Templates",
        "tests"
    };

    iter(words, 3, printString);

    std::cout << "\n\n";
}