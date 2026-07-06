#include <exception>
#include <iostream>
#include <string>

#include "Array.hpp"

template <typename T>
void printArray(const Array<T>& array, const std::string& label)
{
	std::cout << label << " (size = " << array.size() << "): ";
	for (unsigned int i = 0; i < array.size(); ++i)
		std::cout << array[i] << ' ';
	std::cout << std::endl;
}

int main(void)
{
	std::cout << "=== default constructor ===" << std::endl;
	Array<int> empty;
	std::cout << "empty.size() = " << empty.size() << std::endl;

	std::cout << "\n=== sized constructor ===" << std::endl;
	Array<int> numbers(5);
	for (unsigned int i = 0; i < numbers.size(); ++i)
		numbers[i] = static_cast<int>(i * 10);
	printArray(numbers, "numbers");

	std::cout << "\n=== copy constructor ===" << std::endl;
	Array<int> copied(numbers);
	copied[0] = 999;
	printArray(numbers, "original");
	printArray(copied, "copied");

	std::cout << "\n=== assignment operator ===" << std::endl;
	Array<int> assigned;
	assigned = numbers;
	assigned[1] = 777;
	printArray(numbers, "original");
	printArray(assigned, "assigned");

	std::cout << "\n=== string array ===" << std::endl;
	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "array";
	words[2] = "template";
	printArray(words, "words");

	std::cout << "\n=== bounds checking ===" << std::endl;
	try
	{
		std::cout << numbers[5] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught exception: " << e.what() << std::endl;
	}

	return 0;
}