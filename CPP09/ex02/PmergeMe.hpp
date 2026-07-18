
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>

class PmergeMe {

public:

	static void vector_sorter(std::vector<int>& input);
	static void deque_sorter(std::deque<int>& input);

private:
	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);

};

#endif /* PMERGEME_HPP */