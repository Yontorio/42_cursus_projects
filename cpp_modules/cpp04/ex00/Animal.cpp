#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
    std::cout << "Constructing Animal\n";
}

Animal::Animal(const Animal& other) : type(other.type)
{
    std::cout << "Copy Constructing Animal\n";
}

Animal::~Animal()
{
    std::cout << "Destructing Animal\n";
}

Animal& Animal::operator=(const Animal& other)
{
    if (this != &other)
        type = other.type;
    return (*this);
}

void Animal::makeSound() const
{
    std::cout << "Animal scream!\n";
}

std::string Animal::getType() const { return type; }
