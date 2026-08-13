#include "Span.hpp"

Span::Span() : _capacity(0) {}

Span::Span(unsigned int cap) : _capacity(cap) {}

Span::Span(const Span &other) : _capacity(other._capacity),
                                 _storage(other._storage) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _capacity = other._capacity;
        _storage = other._storage;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (_storage.size() >= _capacity)
        throw std::overflow_error("maximum capacity reached!");

    _storage.push_back(number);
}

long Span::longestSpan() const
{
    if (_storage.size() < 2)
        throw std::logic_error("storage has less than 2 numbers");

    return (*std::max_element(_storage.begin(), _storage.end()) -
            *std::min_element(_storage.begin(), _storage.end()));
}

long Span::shortestSpan() const
{
    if (_storage.size() < 2)
        throw std::logic_error("storage has less than 2 numbers");

    std::vector<int> sorted_copy(_storage);
    std::sort(sorted_copy.begin(), sorted_copy.end());

    int shortest = sorted_copy[1] - sorted_copy[0];
    for (size_t i = 1; i < sorted_copy.size(); ++i)
        shortest = std::min(shortest, sorted_copy[i] - sorted_copy[i - 1]);

    return shortest;
}