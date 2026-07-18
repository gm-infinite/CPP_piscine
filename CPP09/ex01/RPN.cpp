
#include "RPN.hpp"

bool input_validator(std::string argument)
{
	int number_count = 0;
	int operation_count = 0;
	for(int i = 0; i < argument.length(); i++)
	{
		if((argument[i] >= '0' && argument[i] <= '9') || argument[i] == ' ')
		{
			number_count++;
			continue;
		}
		else if(argument[i] == '+' || argument[i] == '-' || argument[i] == '*' || argument[i] == '/')
		{
			operation_count++;
			continue; 
		}
		else
		{
			std::cerr << "Error: invalid characters in expression." << std::endl;
			return (false);
		}
	}
	if(number_count != operation_count + 1)
	{
		std::cerr << "Error: invalid number of operands or operators." << std::endl;
		return (false);
	}
	return (true);
}

int RPN_calculator(std::string argument)
{
	std::stack<int> stack;
	for(int i = 0; i < argument.length(); i++)
	{
		if(argument[i] >= '0' && argument[i] <= '9')
			stack.push(argument[i] - '0');
		else if(argument[i] == '+' || argument[i] == '-' || argument[i] == '*' || argument[i] == '/')
		{
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			stack.push(calculate(a, b, argument[i]));
		}
	}

	return (stack.top());
}

int calculate(int a, int b, char op)
{
	if(op == '+')
		return (a + b);
	else if(op == '-')
		return (a - b);
	else if(op == '*')
		return (a * b);
	else if(op == '/')
		return (a / b);
	else
		return (0);
}