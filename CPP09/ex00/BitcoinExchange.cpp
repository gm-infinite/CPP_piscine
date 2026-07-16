
#include "BitcoinExchange.hpp"

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
BitcoinExchange::BitcoinExchange(void) : _data()
{ }

BitcoinExchange::BitcoinExchange(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not find Data.csv");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string date;
        float value;
        if (std::getline(ss, date, ',') && ss >> value)
            this->_data[date] = value;
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data)
{ }

/* ┌───────────────────┐ */
/* │   DESTRUCTOR      │ */
/* └───────────────────┘ */

BitcoinExchange::~BitcoinExchange(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{ 
    if (this != &other)
        this->_data = other._data;
    return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

static bool format_check(const std::string& date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    std::stringstream ss(date);
    int year, month, day;
    char c1, c2;
    ss >> year >> c1 >> month >> c2 >> day;
    if (year < 2009 || year > 2022)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    return true;
}

static bool parse_line(const std::string& line, std::string& date, std::string& valStr)
{
    size_t sep = line.find(" | ");
    if (sep == std::string::npos)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return false;
    }
    date = line.substr(0, sep);
    valStr = line.substr(sep + 3);
    if (!format_check(date))
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return false;
    }
    return true;
}

static bool validate_value(const std::string& valStr, const std::string& line, double& value)
{
    std::istringstream iss(valStr);
    if (!(iss >> value) || iss.peek() != EOF)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return false;
    }
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::printResults(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::string date, valStr;
        if (!parse_line(line, date, valStr))
            continue;

        double value;
        if (!validate_value(valStr, line, value))
            continue;

        std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
        if (it == _data.end() || it->first != date)
        {
            if (it == _data.begin())
            {
                std::cerr << "Error: date out of range." << std::endl;
                continue;
            }
            --it;
        }
        float rate = it->second;
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}