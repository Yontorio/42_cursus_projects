#include "Character.hpp"

Character::Character()
{
    for (int i = 0; i < 4; ++i) _inventory[i] = (AMateria *)0;
}

Character::Character(std::string const & name) : _name(name)
{
    for (int i = 0; i < 4; ++i) _inventory[i] = (AMateria *)0;
}

Character::Character(const Character& other) : _name(other._name)
{
    for (int i = 0; i < 4; i++)
    {
        if (other._inventory[i])
        {
            _inventory[i] = other._inventory[i]->clone();
            continue ;
        }
        _inventory[i] = (AMateria *)0;
    }
}

Character::~Character()
{
    for (int i = 0; i < 4; i++)
        delete _inventory[i];
}

Character& Character::operator=(const Character& other)
{
    if (this != &other)
    {
        _name = other._name;
        for (int i = 0; i < 4; i++)
        {
            delete _inventory[i];
            if (other._inventory[i])
            {
                _inventory[i] = other._inventory[i]->clone();
                continue ;
            }
            _inventory[i] = (AMateria *)0;
        }
    }
    return (*this);
}

std::string const & Character::getName() const { return (_name); }

const AMateria *Character::getInventory(int idx) const
{
    if (idx < 0 || idx >= 4 || !_inventory[idx])
        return (NULL);
    return (_inventory[idx]);
}

void Character::equip(AMateria* materia)
{
    if (!materia)
        return ;
    for (int i = 0; i < 4; i++)
    {
        if (!_inventory[i])
        {
            _inventory[i] = materia;
            return ;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4)
        return ;
    _inventory[idx] = (AMateria *)0;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= 4 || !_inventory[idx])
        return ;
    _inventory[idx]->use(target);
}
