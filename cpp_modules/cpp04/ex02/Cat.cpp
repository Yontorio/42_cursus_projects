#include "Cat.hpp"

Cat::Cat() : AAnimal()
{
    std::cout << "Constructing Cat\n";
    type = "Cat";
    brain = new Brain();
}

Cat::Cat(const Cat& other) : AAnimal(other)
{
    std::cout << "Copy Constructing Cat\n";
    brain = new Brain(*other.brain);
}

Cat::~Cat()
{
    std::cout << "Destructing Cat\n";
    delete brain;
}

Cat& Cat::operator=(const Cat& other)
{
    if (this != &other)
    {
        AAnimal::operator=(other);
        *brain = *other.brain;
    }
    return (*this);
}

void Cat::makeSound() const
{
    std::cout << "Meow Meow!\n";
}

Brain* Cat::getBrain() const { return brain; }

