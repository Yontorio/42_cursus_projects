#include "Cat.hpp"

Cat::Cat()
{
    type = "Cat";
    std::cout << "Constructing Cat\n";
}

Cat::Cat(const Cat& other) : Animal(other)
{
    std::cout << "Copy Constructing Cat\n";
}

Cat::~Cat()
{
    std::cout << "Destructing Cat\n";
}

Cat& Cat::operator=(const Cat& other)
{
    if (this != &other)
        type = other.type;
    return (*this);
}

void Cat::makeSound() const
{
    std::cout << "Meow Meow!\n";
}

