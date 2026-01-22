#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n)
{
    std::cout << "Int constructor called" << std::endl;
    _rawBits = n << _fractionalBits;
}

Fixed::Fixed(const float f)
{
    std::cout << "Float constructor called" << std::endl;
    _rawBits = roundf(f * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        _rawBits = other.getRawBits();
    return *this;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

bool Fixed::operator>(const Fixed &o) const { return _rawBits > o._rawBits; }
bool Fixed::operator<(const Fixed &o) const { return _rawBits < o._rawBits; }
bool Fixed::operator>=(const Fixed &o) const { return _rawBits >= o._rawBits; }
bool Fixed::operator<=(const Fixed &o) const { return _rawBits <= o._rawBits; }
bool Fixed::operator==(const Fixed &o) const { return _rawBits == o._rawBits; }
bool Fixed::operator!=(const Fixed &o) const { return _rawBits != o._rawBits; }

Fixed Fixed::operator+(const Fixed &o) const
{
    Fixed tmp;

    tmp._rawBits = this->_rawBits + o._rawBits;
    return tmp;
}

Fixed Fixed::operator-(const Fixed &o) const
{
    Fixed tmp;

    tmp._rawBits = this->_rawBits - o._rawBits;
    return tmp;
}

Fixed Fixed::operator*(const Fixed &o) const
{
    Fixed tmp;

    tmp._rawBits = ((long)this->_rawBits * o._rawBits) / (1 << _fractionalBits);
    return tmp;
}

Fixed Fixed::operator/(const Fixed &o) const
{
    Fixed tmp;

    tmp._rawBits = ((long)this->_rawBits * (1 << _fractionalBits)) / o._rawBits;
    return tmp;
}

Fixed &Fixed::operator++()
{
    _rawBits++;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed tmp(*this);
    
    _rawBits++;
    return tmp;
}

Fixed &Fixed::operator--()
{
    _rawBits--;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    
    _rawBits--;
    return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    return (a < b) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
    return (a < b) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    return (a > b) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
    return (a > b) ? a : b;
}

int Fixed::getRawBits(void) const { return _rawBits; }
void Fixed::setRawBits(int const raw) { _rawBits = raw; }

float Fixed::toFloat(void) const
{
    return (float)_rawBits / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
    return _rawBits >> _fractionalBits;
}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed)
{
    os << fixed.toFloat();
    return os;
}
