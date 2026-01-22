#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Constructing Brain\n";
    for (int i = 0; i < 100; ++i) _ideas[i] = "";
}

Brain::Brain(const Brain& other)
{
    std::cout << "Copy Constructing Brain\n";
    *this = other;
}

Brain::~Brain()
{
    std::cout << "Destructing Brain\n";
}

Brain& Brain::operator=(const Brain& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 100; ++i)
            _ideas[i] = other._ideas[i];
    }
    return (*this);
}

void Brain::setIdea(int index, const std::string &idea)
{
    if (index >= 0 && index < 100)
        _ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
    if (index >= 0 && index < 100)
        return (_ideas[index]);
    return ("");
}
