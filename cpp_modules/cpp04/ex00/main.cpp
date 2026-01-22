#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "=== Testing Virtual Functions (Polymorphism and Destructors) ===\n";

    const Animal* animal = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << "Dog type: " << dog->getType() << std::endl;
    std::cout << "Cat type: " << cat->getType() << std::endl;

    dog->makeSound();
    cat->makeSound();
    animal->makeSound();

    delete dog;
    delete cat;
    delete animal;

    std::cout << "=== Testing Direct Deletion of Derived Class (Polymorphism and Destructors) ===\n";

    const Dog* dog2 = new Dog();

    std::cout << "dog2 type: " << dog2->getType() << std::endl;

    dog2->makeSound();

    delete dog2;

    std::cout << "\n=== Testing Non-Virtual Functions (No Polymorphism, Improper Destruction) ===\n";

    const WrongAnimal* wc1 = new WrongCat();
    std::cout << "wc1 type: " << wc1->getType() << std::endl;
    wc1->makeSound();

    delete wc1;

    std::cout << "\n=== Testing Direct Deletion of Derived Class (Non-Virtual Base) ===\n";

    WrongCat* wc2 = new WrongCat();
    wc2->makeSound();
    delete wc2;

    return (0);
}
