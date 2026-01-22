#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    std::cout << "----- polymorphism tests -----\n";
    const AAnimal *a = new Dog();
    const AAnimal *b = new Cat();
    a->makeSound();
    b->makeSound();
    delete a;
    delete b;

    std::cout << "\n* animals array test *\n";
    const AAnimal* animals[4];
    for (int i = 0; i < 2; i++)
        animals[i] = new Dog();
    for (int i = 2; i < 4; i++)
        animals[i] = new Cat();
    for (int i = 0; i < 4; i++)
        animals[i]->makeSound();
        
    std::cout << "\n--------- Deep copy test ---------\n";

    std::cout << "\n* create&copy dog1 to dog2 *\n";    
    Dog dog1;
    dog1.getBrain()->setIdea(0, "I am hungry");
    Dog dog2 = dog1;
    std::cout << "dog1 idea: " << dog1.getBrain()->getIdea(0) << "\n";
    std::cout << "dog2 idea: " << dog2.getBrain()->getIdea(0) << "\n";

    std::cout << "\n* changing dog2 *\n";
    dog2.getBrain()->setIdea(0, "I am sleepy");
    std::cout << "dog1 idea: " << dog1.getBrain()->getIdea(0) << "\n";
    std::cout << "dog2 idea: " << dog2.getBrain()->getIdea(0) << "\n";

    std::cout << "\n* assigning dog1 to dog2 *\n";
    dog2 = dog1;
    std::cout << "dog1 idea: " << dog1.getBrain()->getIdea(0) << "\n";
    std::cout << "dog2 idea: " << dog2.getBrain()->getIdea(0) << "\n";

    std::cout << "\n* cleanup *\n";
    for (int i = 0; i < 4; i++)
        delete animals[i];

    return (0);
}
