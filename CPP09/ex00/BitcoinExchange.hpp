
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <stdexcept>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class BitcoinExchange {

public:
    BitcoinExchange(void);
    ~BitcoinExchange(void);
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    BitcoinExchange(const std::string& filename);
    void printResults(const std::string& filename);

private:
    std::map<std::string, float> _data;
};

#endif /* BITCOINEXCHANGE_HPP */