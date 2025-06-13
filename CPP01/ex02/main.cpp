
#include <string>
#include <iostream>

int main(void)
{
	std::string brain = "HI THIS IS BRAIN";
	std::string *stringPTR = &brain;
	std::string& stringREF = brain;

	std::cout 	<< &brain 		<< '\n'
				<< stringPTR	<< '\n'
				<< &stringREF	<< std::endl;

	std::cout 	<< brain 		<< '\n'
				<< *stringPTR	<< '\n'
				<< stringREF	<< std::endl;
}