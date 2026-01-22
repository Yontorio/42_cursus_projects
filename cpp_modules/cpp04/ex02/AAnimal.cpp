#include "AAnimal.hpp"

AAnimal::AAnimal() : type("AAnimal")
{
    std::cout << "Constructing AAnimal\n";
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type)
{
    std::cout << "Copy Constructing AAnimal\n";
}

AAnimal::~AAnimal()
{
    std::cout << "Destructing AAnimal\n";
}

AAnimal& AAnimal::operator=(const AAnimal& other)
{
    if (this != &other)
        type = other.type;
    return *this;
}

std::string AAnimal::getType() const { return type; }
