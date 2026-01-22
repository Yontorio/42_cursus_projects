#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
    std::cout << "Constructing WrongAnimal\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.type)
{
    std::cout << "Copy Constructing WrongAnimal\n";
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "Destructing WrongAnimal\n";
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
    if (this != &other)
        type = other.type;
    return (*this);
}

void WrongAnimal::makeSound() const
{
    std::cout << "WrongAnimal scream!\n";
}

std::string WrongAnimal::getType() const { return type; }
