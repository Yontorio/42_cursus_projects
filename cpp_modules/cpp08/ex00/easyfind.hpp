#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator found = std::find(container.begin(), container.end(), value);
    if (found == container.end())
        throw std::runtime_error("no occurrence is found");
    return found;
}

template <typename T>
typename T::const_iterator easyfind(const T &container, int value)
{
    typename T::const_iterator found = std::find(container.begin(), container.end(), value);
    if (found == container.end())
        throw std::runtime_error("no occurrence is found");
    return found;
}

#endif
