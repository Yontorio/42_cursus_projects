#include "Span.hpp"

#include <iostream>
#include <cstdlib>

int main()
{
    std::cout << "===== Subject Test =====\n";

    try
    {
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest Span : " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span  : " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n===== Overflow Test =====\n";

    try
    {
        Span sp(2);

        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n===== Not Enough Numbers =====\n";

    try
    {
        Span sp(5);

        sp.addNumber(42);

        std::cout << sp.shortestSpan() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n===== Range Test =====\n";

    try
    {
        Span sp(10);

        std::vector<int> values(10);
        for (int i = 0; i < 10; i++)
            values[i] = i + 42;

        sp.addNumbers(values.begin(), values.end());

        std::cout << "Shortest Span : " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span  : " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n===== Large Test =====\n";

    try
    {
        Span sp(20000);
        srand(time(NULL));

        for (int i = 0; i < 20000; i++)
            sp.addNumber(rand());

        std::cout << "Shortest Span : " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span  : " << sp.longestSpan() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
