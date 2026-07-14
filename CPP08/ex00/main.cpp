#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main(void)
{
	/* ──── Vector ──── */
	{
		std::cout << "=== Vector ===" << std::endl;
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		try {
			std::vector<int>::iterator it = easyfind(v, 3);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::vector<int>::iterator it = easyfind(v, 42);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	/* ──── List ──── */
	{
		std::cout << "\n=== List ===" << std::endl;
		std::list<int> l;
		l.push_back(10);
		l.push_back(20);
		l.push_back(30);

		try {
			std::list<int>::iterator it = easyfind(l, 20);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::list<int>::iterator it = easyfind(l, 99);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	/* ──── Deque ──── */
	{
		std::cout << "\n=== Deque ===" << std::endl;
		std::deque<int> d;
		d.push_back(100);
		d.push_back(200);
		d.push_back(300);

		try {
			std::deque<int>::iterator it = easyfind(d, 100);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

		try {
			std::deque<int>::iterator it = easyfind(d, 999);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
