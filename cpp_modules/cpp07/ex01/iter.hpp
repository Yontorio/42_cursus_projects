#ifndef ITER_HPP
# define ITER_HPP

# include<cstddef>

template <typename T>
void iter(T *array, const size_t length, void (*func)(T &))
{
    if (array && func)
    {
        for (size_t i = 0; i < length; ++i)
        {
            func(array[i]);
        }
    }
}

#endif