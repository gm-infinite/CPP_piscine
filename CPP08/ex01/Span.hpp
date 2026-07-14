
#ifndef SPAN_HPP
#define SPAN_HPP
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <climits>


class Span {

public:
	Span(unsigned int N);
	~Span(void);
	Span(const Span& other);
	Span& operator=(const Span& other);

	void addNumber(int number);
	int shortestSpan(void) const;
	int longestSpan(void) const;

	template<typename iterator>
	void addRange(iterator begin, iterator end);

private:
	std::vector<int> array;
	unsigned int  max_int_count;

	Span(void);
};

template<typename iterator>
void Span::addRange(iterator begin, iterator end)
{
	if(this->array.size() + std::distance(begin, end) > this->max_int_count)
		throw std::logic_error("Error: Span::AddRange: not enough capacity");
	this->array.insert(this->array.end(), begin, end);
}

#endif /* SPAN_HPP */