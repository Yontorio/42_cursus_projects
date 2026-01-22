#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; ++i) _storage[i] = (AMateria *)0;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
    for (int i = 0; i < 4; i++)
    {
        if (other._storage[i])
        {
            _storage[i] = other._storage[i]->clone();
            continue ;
        }
        _storage[i] = (AMateria *)0;
    }
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; i++)
        delete _storage[i];
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 4; i++)
        {
            delete _storage[i];
            if (other._storage[i])
            {
                _storage[i] = other._storage[i]->clone();
                continue ;
            }
            _storage[i] = (AMateria *)0;
        }
    }
    return (*this);
}

void MateriaSource::learnMateria(AMateria* materia)
{
    if (!materia)
        return ;
    for (int i = 0; i < 4; i++)
    {
        if (!_storage[i])
        {
            _storage[i] = materia;
            return ;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
    for (int i = 0; i < 4; i++)
    {
        if (_storage[i] && _storage[i]->getType() == type)
            return (_storage[i]->clone());
    }
    return ((AMateria *)0);
}
