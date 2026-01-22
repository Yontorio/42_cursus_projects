#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
    : ClapTrap("Default_clap_name"), name("Default")
{
    hitPoints = FragTrap::hitPoints;
    energyPoints = 50;
    attackDamage = FragTrap::attackDamage;

    std::cout << "DiamondTrap default constructor called\n";
}

DiamondTrap::DiamondTrap(const std::string &n)
    : ClapTrap(n + "_clap_name"), name(n)
{
    hitPoints = FragTrap::hitPoints;
    energyPoints = 50;
    attackDamage = FragTrap::attackDamage;

    std::cout << "DiamondTrap constructor called for " << name << "\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
    : ClapTrap(other), ScavTrap(other), FragTrap(other), name(other.name)
{
    std::cout << "DiamondTrap copy constructor called\n";
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &other)
{
    if (this != &other)
    {
        ClapTrap::operator=(other);
        name = other.name;
    }
    return *this;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap destructor called for " << name << "\n";
}

void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap name: " << name << "\n";
    std::cout << "ClapTrap name: " << ClapTrap::name << "\n";
}
