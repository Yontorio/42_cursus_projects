#include "MutantStack.hpp"

#include <iostream>
#include <list>

int main()
{
    std::cout << "========== Subject Test ==========\n";
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << "Top : " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "Size: " << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    std::cout << "MutantStack contents:\n";
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    std::cout << "\n========== Copy to std::stack ==========\n";
    std::stack<int> s(mstack);
    while (!s.empty())
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }

    std::cout << "\n========== Compare with std::list ==========\n";
    {
        std::list<int> lst;
        lst.push_back(5);
        lst.push_back(17);
        std::cout << "Top : " << lst.back() << std::endl;
        lst.pop_back();
        std::cout << "Size: " << lst.size() << std::endl;
        lst.push_back(3);
        lst.push_back(5);
        lst.push_back(737);
        lst.push_back(0);
        std::cout << "list contents:\n";
        std::list<int>::iterator it = lst.begin();
        std::list<int>::iterator ite = lst.end();
        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }

    return 0;
}
