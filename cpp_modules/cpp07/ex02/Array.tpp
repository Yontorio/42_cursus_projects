template <typename T>
Array<T>::Array() : _size(0), _array(NULL) { }

template <typename T>
Array<T>::Array(unsigned int n) : _size(n), _array(new T[n]()) { }

template <typename T>
Array<T>::Array(const Array<T> &other) : _size(other._size), _array(new T[_size])
{
    for (unsigned int i = 0; i < _size; ++i)
    {
        _array[i] = other._array[i];
    }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &other)
{
    if (this != &other)
    {
        T* tmp = new T[other._size];
        for (unsigned int i = 0; i < other._size; ++i)
        {
            tmp[i] = other._array[i];
        }
        delete[] _array;
        _array = tmp;
        _size = other._size;
    }
    return *this;
}

template <typename T>
Array<T>::~Array() { delete[] _array; }

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
    if (index >= _size)
        throw std::out_of_range("Index out of range");
    return _array[index];
}

template <typename T>
const T &Array<T>::operator[](unsigned int index) const
{
    if (index >= _size)
        throw std::out_of_range("Index out of range");
    return _array[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
    return _size;
}
