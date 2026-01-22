#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
    FragTrap f("Worrior");
    ScavTrap s("Guardian");

    f.attack("Enemy");
    s.guardGate();
    f.takeDamage(40);
    f.beRepaired(10);
    f.highFivesGuys();

    return 0;
}
