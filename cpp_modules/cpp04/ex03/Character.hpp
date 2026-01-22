#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter
{
    private:
        std::string _name;
        AMateria* _inventory[4];

    public:
        Character();
        Character(std::string const & name);
        Character(const Character& other);
        ~Character();

        Character& operator=(const Character& other);

        std::string const & getName() const;
        const AMateria *getInventory(int idx) const;
        void equip(AMateria* m);
        void unequip(int idx);
        void use(int idx, ICharacter& target);
};

#endif
