#include "ScavTrap.hpp"

int main()
{
    ScavTrap s("Guardian");

    s.attack("Enemy");
    s.takeDamage(30);
    s.beRepaired(20);
    s.guardGate();

    return 0;
}
