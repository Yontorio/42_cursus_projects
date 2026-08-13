#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>

template <class T>
class Array
{
    private:
        unsigned int _size;
        T *_array;
    public:
        Array();
        Array(unsigned int n);
        Array(const Array &other);
        Array &operator=(const Array &other);
        ~Array();
        T &operator[](unsigned int index);
        const T &operator[](unsigned int index) const;
        unsigned int size() const;
};

#include "Array.tpp"

#endif
