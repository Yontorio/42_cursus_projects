#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "Base.hpp"
#include "functions.hpp"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for (int i = 0; i < 5; ++i)
    {
        std::cout << "\n--- Test Iteration " << (i + 1) << " ---" << std::endl;
        
        Base* instance = generate();
        
        std::cout << "Identify using pointer:   ";
        identify(instance);
        
        if (instance != NULL)
        {
            std::cout << "Identify using reference: ";
            identify(*instance);
        }
        delete instance;
        usleep(100000);
    }
    return 0;
}
