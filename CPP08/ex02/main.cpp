#include <iostream>
#include <list>
#include <string>
#include "MutantStack.hpp"

int main(void)
{
	/* ──── Subject test with MutantStack ──── */
	{
		std::cout << "=== MutantStack ===" << std::endl;
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << "Top: " << mstack.top() << std::endl;

		mstack.pop();

		std::cout << "Size: " << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;

		std::cout << "Elements:" << std::endl;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}

		std::stack<int> s(mstack);
	}

	/* ──── Same test with std::list ──── */
	{
		std::cout << "\n=== Same test with std::list ===" << std::endl;
		std::list<int> lst;

		lst.push_back(5);
		lst.push_back(17);

		std::cout << "Top: " << lst.back() << std::endl;

		lst.pop_back();

		std::cout << "Size: " << lst.size() << std::endl;

		lst.push_back(3);
		lst.push_back(5);
		lst.push_back(737);
		lst.push_back(0);

		std::list<int>::iterator lit = lst.begin();
		std::list<int>::iterator lite = lst.end();

		++lit;
		--lit;

		std::cout << "Elements:" << std::endl;
		while (lit != lite)
		{
			std::cout << *lit << std::endl;
			++lit;
		}
	}

	/* ──── Reverse iteration ──── */
	{
		std::cout << "\n=== Reverse iteration ===" << std::endl;
		MutantStack<int> mstack;
		mstack.push(1);
		mstack.push(2);
		mstack.push(3);

		for (MutantStack<int>::reverse_iterator rit = mstack.rbegin();
			rit != mstack.rend(); ++rit)
			std::cout << *rit << std::endl;
	}

	/* ──── Copy constructor & assignment ──── */
	{
		std::cout << "\n=== Copy test ===" << std::endl;
		MutantStack<int> mstack;
		mstack.push(1);
		mstack.push(2);
		mstack.push(3);

		MutantStack<int> copy(mstack);
		std::cout << "Copy size: " << copy.size() << std::endl;
		std::cout << "Copy top: " << copy.top() << std::endl;

		MutantStack<int> assigned;
		assigned = mstack;
		std::cout << "Assigned size: " << assigned.size() << std::endl;
		std::cout << "Assigned top: " << assigned.top() << std::endl;
	}

	/* ──── Subject test with MutantStack<std::string> ──── */
	{
		std::cout << "\n=== MutantStack<std::string> ===" << std::endl;
		MutantStack<std::string> mstack;

		mstack.push("5");
		mstack.push("17");

		std::cout << "Top: " << mstack.top() << std::endl;

		mstack.pop();

		std::cout << "Size: " << mstack.size() << std::endl;

		mstack.push("3");
		mstack.push("5");
		mstack.push("737");
		mstack.push("0");

		MutantStack<std::string>::iterator it = mstack.begin();
		MutantStack<std::string>::iterator ite = mstack.end();

		++it;
		--it;

		std::cout << "Elements:" << std::endl;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}

		std::stack<std::string> s(mstack);
	}

	/* ──── Same test with std::list<std::string> ──── */
	{
		std::cout << "\n=== Same test with std::list<std::string> ===" << std::endl;
		std::list<std::string> lst;

		lst.push_back("5");
		lst.push_back("17");

		std::cout << "Top: " << lst.back() << std::endl;

		lst.pop_back();

		std::cout << "Size: " << lst.size() << std::endl;

		lst.push_back("3");
		lst.push_back("5");
		lst.push_back("737");
		lst.push_back("0");

		std::list<std::string>::iterator lit = lst.begin();
		std::list<std::string>::iterator lite = lst.end();

		++lit;
		--lit;

		std::cout << "Elements:" << std::endl;
		while (lit != lite)
		{
			std::cout << *lit << std::endl;
			++lit;
		}
	}

	/* ──── Reverse iteration with std::string ──── */
	{
		std::cout << "\n=== Reverse iteration with std::string ===" << std::endl;
		MutantStack<std::string> mstack;
		mstack.push("1");
		mstack.push("2");
		mstack.push("3");

		for (MutantStack<std::string>::reverse_iterator rit = mstack.rbegin();
			rit != mstack.rend(); ++rit)
			std::cout << *rit << std::endl;
	}

	/* ──── Copy constructor & assignment with std::string ──── */
	{
		std::cout << "\n=== Copy test with std::string ===" << std::endl;
		MutantStack<std::string> mstack;
		mstack.push("1");
		mstack.push("2");
		mstack.push("3");

		MutantStack<std::string> copy(mstack);
		std::cout << "Copy size: " << copy.size() << std::endl;
		std::cout << "Copy top: " << copy.top() << std::endl;

		MutantStack<std::string> assigned;
		assigned = mstack;
		std::cout << "Assigned size: " << assigned.size() << std::endl;
		std::cout << "Assigned top: " << assigned.top() << std::endl;
	}

	return 0;
}
