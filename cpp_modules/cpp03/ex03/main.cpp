#include "DiamondTrap.hpp"

int main()
{
    DiamondTrap d("Worrior");

    d.attack("Enemy");
    d.guardGate();
    d.takeDamage(30);
    d.beRepaired(20);
    d.whoAmI();

    return 0;
}
