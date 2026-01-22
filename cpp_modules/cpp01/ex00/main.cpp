#include "Zombie.hpp"

int main()
{
    randomChump("Stacky");
    Zombie* heapZombie = newZombie("Heapy");
    heapZombie->announce();
    delete heapZombie;
    return (0);
}
