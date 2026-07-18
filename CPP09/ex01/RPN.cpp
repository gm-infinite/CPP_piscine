
#include "RPN.hpp"

/* ┌──────────────────┐ */
/* │   CONSTRUCTORS   │ */
/* └──────────────────┘ */
RPN::RPN(void) : _stack(), _result(0)
{ }

RPN::RPN(const std::string& expression) : _stack(), _result(0)
{
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (token.size() == 1 && (token[0] == '+' || token[0] == '-'
			|| token[0] == '*' || token[0] == '/'))
		{
			if (this->_stack.size() < 2)
				throw std::runtime_error("Error");
			int a = this->_stack.top();
			this->_stack.pop();
			int b = this->_stack.top();
			this->_stack.pop();
			if (token[0] == '+')
				this->_stack.push(b + a);
			else if (token[0] == '-')
				this->_stack.push(b - a);
			else if (token[0] == '*')
				this->_stack.push(b * a);
			else if (token[0] == '/')
			{
				if (a == 0)
					throw std::runtime_error("Error");
				this->_stack.push(b / a);
			}
		}
		else if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
		{
			this->_stack.push(token[0] - '0');
		}
		else
		{
			throw std::runtime_error("Error");
		}
	}
	if (this->_stack.size() != 1)
		throw std::runtime_error("Error");
	this->_result = this->_stack.top();
}

RPN::RPN(const RPN& other) : _stack(other._stack), _result(other._result)
{ }

/* ┌───────────────────┐ */
/* │   DESTRUCTOR      │ */
/* └───────────────────┘ */

RPN::~RPN(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
		this->_result = other._result;
	}
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

int RPN::getResult(void) const
{
	return (this->_result);
}