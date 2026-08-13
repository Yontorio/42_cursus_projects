#include "ScalarConverter.hpp"

namespace
{
    bool parsePseudo(const std::string &s, double &value)
    {
        if (s == "nan" || s == "nanf")
        {
            value = std::numeric_limits<double>::quiet_NaN();
            return true;
        }
        if (s == "inf" || s == "inff" || s == "+inf" || s == "+inff")
        {
            value = std::numeric_limits<double>::infinity();
            return true;
        }
        if (s == "-inf" || s == "-inff")
        {
            value = -std::numeric_limits<double>::infinity();
            return true;
        }
        return false;
    }

    bool parseNumberAsDouble(const std::string &s, double &value)
    {
        if (s.empty())
            return false;

        char *endptr = NULL;
        double v = std::strtod(s.c_str(), &endptr);

        if (endptr == s.c_str() || *endptr != '\0')
            return false;

        value = v;
        return true;
    }

    bool parseLiteral(const std::string &literal, double &value)
    {
        if (literal.empty())
            return false;

        if (parsePseudo(literal, value))
            return true;

        if (literal.length() == 1 &&
            std::isprint(static_cast<unsigned char>(literal[0])) &&
            !std::isdigit(static_cast<unsigned char>(literal[0])))
        {
            value = static_cast<double>(literal[0]);
            return true;
        }

        std::string target = literal;
        if (literal.length() > 1 &&
            std::tolower(static_cast<unsigned char>(literal[literal.length() - 1])) == 'f')
        {
            target = literal.substr(0, literal.length() - 1);

            if (target.find('.') == std::string::npos &&
                target.find('e') == std::string::npos &&
                target.find('E') == std::string::npos)
                return false;
        }
        return parseNumberAsDouble(target, value);
    }


    bool isWholeNumber(double v)
    {
        return !std::isnan(v) && !std::isinf(v) && v == std::floor(v);
    }

    void printChar(double v)
    {
        std::cout << "char: ";
        if (std::isnan(v) || std::isinf(v) || !isWholeNumber(v) || v < 0.0 || v > 127.0)
        {
            std::cout << "impossible\n";
            return;
        }
        char c = static_cast<char>(v);
        if (!std::isprint(static_cast<unsigned char>(c)))
        {
            std::cout << "Non displayable\n";
            return;
        }
        std::cout << "'" << c << "'\n";
    }

    void printInt(double v)
    {
        std::cout << "int: ";
        if (std::isnan(v) || std::isinf(v) || !isWholeNumber(v) ||
            v < std::numeric_limits<int>::min() || v > std::numeric_limits<int>::max())
        {
            std::cout << "impossible\n";
            return;
        }
        std::cout << static_cast<int>(v) << "\n";
    }

    void printFloat(double v)
    {
        std::cout << "float: ";
        if (std::isnan(v))
        {
            std::cout << "nanf\n";
            return;
        }
        if (std::isinf(v))
        {
            std::cout << (v < 0 ? "-inff\n" : "+inff\n");
            return;
        }

        float f = static_cast<float>(v);
        if (std::isinf(f))
        {
            std::cout << (f < 0 ? "-inff\n" : "+inff\n");
            return;
        }

        std::ostringstream oss;
        if (isWholeNumber(v))
            oss << std::fixed << std::setprecision(1) << f;
        else
            oss << f;
        oss << 'f';
        std::cout << oss.str() << "\n";
    }

    void printDouble(double v)
    {
        std::cout << "double: ";
        if (std::isnan(v))
        {
            std::cout << "nan\n";
            return;
        }
        if (std::isinf(v))
        {
            std::cout << (v < 0 ? "-inf\n" : "+inf\n");
            return;
        }

        std::ostringstream oss;
        if (isWholeNumber(v))
            oss << std::fixed << std::setprecision(1) << v;
        else
            oss << v;
        std::cout << oss.str() << "\n";
    }

    void printImpossible()
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
    }
}

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &literal)
{
    double value;

    if (!parseLiteral(literal, value))
    {
        printImpossible();
        return;
    }

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}
