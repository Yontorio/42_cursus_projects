#include "ClapTrap.hpp"

int main()
{
    ClapTrap a("Worrior");
    ClapTrap b("Enemy");

    a.attack("Enemy");
    b.takeDamage(3);
    b.beRepaired(2);

    return 0;
}
