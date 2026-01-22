#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    type = "WrongCat";
    std::cout << "Constructing WrongCat\n";
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
    std::cout << "Copy Constructing WrongCat\n";
}

WrongCat::~WrongCat()
{
    std::cout << "Destructing WrongCat\n";
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
    if (this != &other)
        type = other.type;
    return (*this);
}

void WrongCat::makeSound() const
{
    std::cout << "Meow Meow!\n";
}

