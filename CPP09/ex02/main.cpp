
#include "PmergeMe.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>

int main(int ac, char** av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::vector<int> vec;
	std::deque<int> deq;

	for (int i = 1; i < ac; i++)
	{
		std::string arg(av[i]);
		if (arg.empty())
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		for (size_t j = 0; j < arg.size(); j++)
		{
			if (!std::isdigit(arg[j]))
			{
				std::cerr << "Error" << std::endl;
				return (1);
			}
		}
		long num = std::atol(arg.c_str());
		if (num < 0 || num > 2147483647)
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}
		vec.push_back(static_cast<int>(num));
		deq.push_back(static_cast<int>(num));
	}

	std::cout << "Before:";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << " " << vec[i];
	std::cout << std::endl;

	clock_t vec_start = clock();
	PmergeMe::vector_sorter(vec);
	clock_t vec_end = clock();

	clock_t deq_start = clock();
	PmergeMe::deque_sorter(deq);
	clock_t deq_end = clock();

	std::cout << "After:";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << " " << vec[i];
	std::cout << std::endl;

	double vec_time = static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC * 1000.0;
	double deq_time = static_cast<double>(deq_end - deq_start) / CLOCKS_PER_SEC * 1000.0;

	std::cout << "Time to process a range of " << vec.size()
		<< " elements with std::vector : " << vec_time << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
		<< " elements with std::deque  : " << deq_time << " us" << std::endl;

	return (0);
}