#include "Dog.hpp"

Dog::Dog() : AAnimal()
{
    std::cout << "Constructing Dog\n";
    type = "Dog";
    brain = new Brain();
}

Dog::Dog(const Dog& other) : AAnimal(other)
{
    std::cout << "Copy Constructing Dog\n";
    brain = new Brain(*other.brain);
}

Dog::~Dog()
{
    std::cout << "Destructing Dog\n";
    delete brain;
}

Dog& Dog::operator=(const Dog& other)
{
    if (this != &other)
    {
        AAnimal::operator=(other);
        *brain = *other.brain;
    }
    return (*this);
}

void Dog::makeSound() const
{
    std::cout << "Woof Woof!\n";
}

Brain* Dog::getBrain() const { return brain; }

