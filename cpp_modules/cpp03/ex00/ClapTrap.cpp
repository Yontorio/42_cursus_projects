#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : name("Default"), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap default constructor called\n";
}

ClapTrap::ClapTrap(const std::string &name)
    : name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap constructor called for " << name << "\n";
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
    *this = other;
    std::cout << "ClapTrap copy constructor called\n";
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    if (this != &other)
    {
        name = other.name;
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
    }
    return *this;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap destructor called for " << name << "\n";
}

void ClapTrap::attack(const std::string &target)
{
    if (energyPoints == 0 || hitPoints == 0)
    {
        std::cout << "ClapTrap " << name << " unable to attack\n";
        return;
    }
    energyPoints--;
    std::cout << "ClapTrap " << name << " attacks " << target
              << ", causing " << attackDamage << " points of damage!\n";
}
void ClapTrap::takeDamage(unsigned int amount)
{
    if (hitPoints <= 0)
    {
        std::cout << "ClapTrap " << name
                  << " is already destroyed.\n";
        return;
    }

    if (amount >= hitPoints)
        hitPoints = 0;
    else
        hitPoints -= amount;

    std::cout << "ClapTrap " << name
              << " takes " << amount
              << " amount damage, hit points are down to " << hitPoints << ".\n";
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (hitPoints <= 0)
    {
        std::cout << "ClapTrap " << name
                  << " is destroyed and cannot be repaired.\n";
        return;
    }

    if (energyPoints <= 0)
    {
        std::cout << "ClapTrap " << name
                  << " has no energy left to repair.\n";
        return;
    }

    if (hitPoints + amount > 10)
        hitPoints = 10;
    else
        hitPoints += amount;

    energyPoints--;

    std::cout << "ClapTrap " << name
              << " repairs " << amount
              << " hit points, hit points now are " << hitPoints << ".\n";
}
