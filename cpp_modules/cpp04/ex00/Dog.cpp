#include "Dog.hpp"

Dog::Dog()
{
    type = "Dog";
    std::cout << "Constructing Dog\n";
}

Dog::Dog(const Dog& other) : Animal(other)
{
    std::cout << "Copy Constructing Dog\n";
}

Dog::~Dog()
{
    std::cout << "Destructing Dog\n";
}

Dog& Dog::operator=(const Dog& other)
{
    if (this != &other)
        type = other.type;
    return (*this);
}

void Dog::makeSound() const
{
    std::cout << "Woof Woof!\n";
}

