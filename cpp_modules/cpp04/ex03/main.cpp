#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

void track(AMateria* materia, int flag)
{
    static AMateria* allocated[100];
    static int allocCount = 0;

    if (flag)
    {
        if (materia)
            allocated[allocCount++] = materia;
    }
    else
    {
        for (int i = 0; i < allocCount; i++)
            delete allocated[i];
    }
}

int main()
{
    std::cout << "===== BASIC SUBJECT TEST =====\n";

    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;

    tmp = src->createMateria("ice");
    // track(tmp, 1);
    me->equip(tmp); // me [0]

    tmp = src->createMateria("cure");
    track(tmp, 1);
    me->equip(tmp); // me [1]

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    std::cout << "\n===== UNKNOWN MATERIA TEST =====\n";
    tmp = src->createMateria("fire");
    // track(tmp, 1);
    if (!tmp)
        std::cout << "Unknown materia\n";

    std::cout << "\n===== INVENTORY LIMIT TEST =====\n";
    tmp = src->createMateria("ice");
    // track(tmp, 1);
    me->equip(tmp); // me [2]

    tmp = src->createMateria("cure");
    // track(tmp, 1);
    me->equip(tmp); // me [3]

    tmp = src->createMateria("ice");
    track(tmp, 1);
    me->equip(tmp); // inventory full

    std::cout << "\n===== INVALID USE TEST =====\n";
    me->use(4, *bob);
    me->use(-1, *bob);

    std::cout << "\n===== UNEQUIP TEST =====\n";
    me->unequip(1);
    me->use(1, *bob); // nothing happened

    std::cout << "\n===== RE-EQUIP AFTER UNEQUIP =====\n";
    tmp = src->createMateria("cure");
    // track(tmp, 1);
    me->equip(tmp);
    me->use(1, *bob);

    std::cout << "\n===== MULTIPLE CHARACTERS TEST =====\n";
    ICharacter* alice = new Character("alice");
    ICharacter* eve   = new Character("eve");

    tmp = src->createMateria("ice");
    // track(tmp, 1);
    alice->equip(tmp);

    tmp = src->createMateria("cure");
    // track(tmp, 1);
    alice->equip(tmp);

    tmp = src->createMateria("cure");
    // track(tmp, 1);
    eve->equip(tmp);

    alice->use(0, *eve);
    alice->use(1, *bob);
    eve->use(0, *alice);

    std::cout << "\n===== DEEP COPY TEST =====\n";
    Character* clone = new Character(*(Character*)me);
    clone->use(0, *bob); // deep copied and works
    track((AMateria *)clone->getInventory(0), 1);
    clone->unequip(0);
    clone->use(0, *bob); // no longer working
    me->use(0, *bob); // not effected thanks to deep coping

    std::cout << "\n===== ASSIGNMENT OPERATOR TEST =====\n";
    Character assigned("assigned");
    assigned = *(Character*)me;
    assigned.use(0, *bob);
    track((AMateria *)assigned.getInventory(0), 1);
    assigned.unequip(0);
    assigned.use(0, *bob);
    me->use(0, *bob);

    std::cout << "\n===== CLEANUP =====\n";

    delete clone;
    delete alice;
    delete eve;
    delete bob;
    delete me;
    delete src;

    track(NULL, 0);

    std::cout << "===== END =====" << std::endl;
    
    return 0;
}
