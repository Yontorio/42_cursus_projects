#include "Cat.hpp"

Cat::Cat() : Animal()
{
    std::cout << "Constructing Cat\n";
    type = "Cat";
    brain = new Brain();
}

Cat::Cat(const Cat& other) : Animal(other)
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
        Animal::operator=(other);
        *brain = *other.brain;
    }
    return (*this);
}

void Cat::makeSound() const
{
    std::cout << "Meow Meow!\n";
}

Brain* Cat::getBrain() const { return brain; }
