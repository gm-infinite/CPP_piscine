#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void print(T const &elem)
{
	std::cout << elem << " ";
}

void increment(int &elem)
{
	elem += 1;
}

struct Point
{
	int x;
	int y;
};

void printPoint(Point const &p)
{
	std::cout << "(" << p.x << "," << p.y << ") ";
}


int main(void)
{
	// int array: read-only iteration with a function template
	int ints[] = {1, 2, 3, 4, 5};
	size_t const intsLen = sizeof(ints) / sizeof(ints[0]);

	std::cout << "ints: ";
	iter(ints, intsLen, print<int>);
	std::cout << std::endl;

	// same array: mutate in place with a non-const reference function
	iter(ints, intsLen, increment);
	std::cout << "ints incremented: ";
	iter(ints, intsLen, print<int>);
	std::cout << std::endl;

	// const array: only a const-reference function can be used
	int const constInts[] = {10, 20, 30};
	size_t const constIntsLen = sizeof(constInts) / sizeof(constInts[0]);

	std::cout << "const ints: ";
	iter(constInts, constIntsLen, print<int>);
	std::cout << std::endl;

	// string array: any type works, not just int
	std::string strings[] = {"Hello", "42", "iter"};
	size_t const stringsLen = sizeof(strings) / sizeof(strings[0]);

	std::cout << "strings: ";
	iter(strings, stringsLen, print<std::string>);
	std::cout << std::endl;

	// custom type array with its own dedicated print function
	Point points[] = {{1, 1}, {2, 4}, {3, 9}};
	size_t const pointsLen = sizeof(points) / sizeof(points[0]);

	std::cout << "points: ";
	iter(points, pointsLen, printPoint);
	std::cout << std::endl;

	return (0);
}