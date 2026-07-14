
#include "Span.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Span::Span(void) : array(std::vector<int>()), max_int_count(0)
{ }

Span::Span(unsigned int N) : array(std::vector<int>()), max_int_count(N)
{ }

Span::Span(const Span& other) : array(std::vector<int>(other.array)), max_int_count(other.max_int_count)
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Span::~Span(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Span& Span::operator=(const Span& other)
{
	if(this != &other)
	{
		this->array = other.array;
		this->max_int_count = other.max_int_count;
	}
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

void Span::addNumber(int number)
{
    if (this->array.size() >= this->max_int_count)
        throw std::logic_error("Logic_error: Span::addNumber: the Span is already full");
    this->array.push_back(number);
}

int Span::shortestSpan(void) const
{
    if (this->max_int_count < 2)
        throw std::logic_error("Logic_error: Span::shortestSpan: capacity is less than 2");
    if (this->array.empty())
        throw std::logic_error("Logic_error: Span::shortestSpan: array is empty");
    if (this->array.size() <= 1)
        throw std::logic_error("Logic_error: Span::shortestSpan: does not have enough numbers");
    std::vector<int> temp(this->array);
    std::sort(temp.begin(), temp.end());
    
	std::vector<int> sorted(this->array);
    std::sort(sorted.begin(), sorted.end());

    unsigned int minSpan = static_cast<unsigned int>(sorted[1] - sorted[0]);
    for (size_t i = 2; i < sorted.size(); i++)
    {
        unsigned int diff = static_cast<unsigned int>(sorted[i] - sorted[i - 1]);
        if (diff < minSpan)
            minSpan = diff;
    }
    return minSpan;
}

int Span::longestSpan(void) const
{
    if (this->max_int_count < 2)
        throw std::logic_error("Logic_error: Span::longestSpan: capacity is less than 2");
    if (this->array.empty())
        throw std::logic_error("Logic_error: Span::longestSpan: array is empty");
    if (this->array.size() <= 1)
        throw std::logic_error("Logic_error: Span::longestSpan: does not have enough numbers");

    return (*(std::max_element(this->array.begin(), this->array.end())) -  *(std::min_element(this->array.begin(), this->array.end())));
}
