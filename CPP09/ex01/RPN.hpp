
#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

class RPN {

public:
    ~RPN(void);
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);

    RPN(const std::string& expression);
    int getResult(void) const;

private:
    std::stack<int> _stack;
    int             _result;

    RPN(void);
};

#endif /* RPN_HPP */