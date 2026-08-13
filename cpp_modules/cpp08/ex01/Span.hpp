#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <stdexcept>

class Span
{
    private:
        unsigned int _capacity;
        std::vector<int> _storage;

    public:
        Span();
        Span(unsigned int cap);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span();

        void addNumber(int number);
        long shortestSpan() const;
        long longestSpan() const;

        template <typename Iterator>
        void addNumbers(Iterator first, Iterator last)
        {
            long count = std::distance(first, last);
            if (count < 0)
                throw std::logic_error("Invalid distance");
            if (static_cast<size_t>(count) > _capacity - _storage.size())
                throw std::overflow_error("maximum capacity reached!");
            _storage.insert(_storage.end(), first, last);
        }
};
#endif
