
#include "ScalarConverter.hpp"
#include <cstdlib>   // atoi, strtol, strtod, strtof, rand
#include <climits>   // INT_MIN, INT_MAX
#include <cfloat>    // FLT_MIN, FLT_MAX
#include <cmath>     // isnan, isinf
#include <cctype>    // isprint, isdigit
#include <iostream>
#include <exception>

enum LiteralType { CHAR, INT, FLOAT, DOUBLE, INVALID };

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
ScalarConverter::ScalarConverter(void)
{ }

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
    (void)other;  // Suppress warning
}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

ScalarConverter::~ScalarConverter(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
    (void)other;
    return *this;  // Missing!
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

static LiteralType detectType(const std::string& literal)
{
    if (literal.empty())
        return INVALID;
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
        return CHAR;
    if (literal == "+inf" || literal == "-inf" || literal == "nan")
        return DOUBLE;
    if (literal == "+inff" || literal == "-inff" || literal == "nanf")
        return FLOAT;
    
    // Validate before assuming INT/FLOAT/DOUBLE
    bool hasDecimal = false;
    bool hasF = false;
    size_t start = 0;
    
    if (literal[0] == '+' || literal[0] == '-')
        start = 1;
    
    if (start >= literal.length())
        return INVALID;
    
    for (size_t i = start; i < literal.length(); i++)
    {
        if (literal[i] == '.')
        {
            if (hasDecimal)
                return INVALID;
            hasDecimal = true;
        }
        else if (literal[i] == 'f' && i == literal.length() - 1)
        {
            hasF = true;
        }
        else if (!std::isdigit(literal[i]))
        {
            return INVALID;
        }
    }
    
    if (hasF)
        return FLOAT;
    if (hasDecimal)
        return DOUBLE;
    return INT;
}

static void printFromChar(char c)
{
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void printFromInt(int i)
{
    // int → char
    if (i < 0 || i > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(i))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
    
    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

static void printFromFloat(float f)
{
    bool isSpecial = std::isnan(f) || std::isinf(f);

    if (isSpecial || f < 0 || f > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(f)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
    
    if (isSpecial || f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    std::cout << "float: " << f;
    if (!isSpecial && f == static_cast<int>(f))
        std::cout << ".0";
    std::cout << "f" << std::endl;
    
    std::cout << "double: " << static_cast<double>(f);
    if (!isSpecial && f == static_cast<int>(f))
        std::cout << ".0";
    std::cout << std::endl;
}

static void printFromDouble(double d)
{
    bool isSpecial = std::isnan(d) || std::isinf(d);
    
    if (isSpecial || d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(d)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

    if (isSpecial || d < INT_MIN || d > INT_MAX)
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    
    std::cout << "float: " << static_cast<float>(d);
    if (!isSpecial && d == static_cast<int>(d))
        std::cout << ".0";
    std::cout << "f" << std::endl;
    
    std::cout << "double: " << d;
    if (!isSpecial && d == static_cast<int>(d))
        std::cout << ".0";
    std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
    LiteralType type = detectType(literal);
    
    switch(type)
    {
        case CHAR:
        {
            char c = literal[1];
            printFromChar(c);
            break;
        }
        case INT:
        {
            double d = std::strtod(literal.c_str(), NULL);
            if (d < INT_MIN || d > INT_MAX) {
                std::cout << "integer overflow accured." << std::endl;
                return;
            }
            int i = static_cast<int>(std::strtol(literal.c_str(), NULL, 10));
            printFromInt(i);
            break;
        }
        case FLOAT:
        {
            float f = static_cast<float>(std::strtod(literal.c_str(), NULL));
            printFromFloat(f);
            break;
        }
        case DOUBLE:
        {
            double d = std::strtod(literal.c_str(), NULL);
            printFromDouble(d);
            break;
        }
        case INVALID:
            std::cout << "Invalid type entered." << std::endl;
            return;
    }
}