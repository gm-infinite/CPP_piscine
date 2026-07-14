#include <iostream>
#include <vector>
#include "Span.hpp"

int main(void)
{
	/* ──── Subject test ──── */
	{
		std::cout << "=== Subject test ===" << std::endl;
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;  // 2
		std::cout << sp.longestSpan() << std::endl;    // 14
	}

	/* ──── Overflow test ──── */
	{
		std::cout << "\n=== Overflow test ===" << std::endl;
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		try {
			sp.addNumber(42);
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	/* ──── Too few elements ──── */
	{
		std::cout << "\n=== Too few elements ===" << std::endl;

		Span empty(0);
		try {
			std::cout << empty.shortestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}

		Span one(1);
		one.addNumber(42);
		try {
			std::cout << one.longestSpan() << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	/* ──── 10,000 numbers with range add ──── */
	{
		std::cout << "\n=== 10,000 numbers ===" << std::endl;
		Span big(10000);
		std::vector<int> nums;
		for (int i = 0; i < 10000; i++)
			nums.push_back(i);
		big.addRange(nums.begin(), nums.end());
		std::cout << "Shortest: " << big.shortestSpan() << std::endl;  // 1
		std::cout << "Longest:  " << big.longestSpan() << std::endl;   // 9999
	}

	/* ──── Range add overflow ──── */
	{
		std::cout << "\n=== Range add overflow ===" << std::endl;
		Span small(3);
		small.addNumber(1);
		std::vector<int> tooMany;
		tooMany.push_back(2);
		tooMany.push_back(3);
		tooMany.push_back(4);
		try {
			small.addRange(tooMany.begin(), tooMany.end());
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	return 0;
}
