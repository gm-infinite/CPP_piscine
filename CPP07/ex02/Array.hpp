
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array {

public:
	Array(void);
	Array(unsigned int n);
	~Array(void);
	Array(const Array& other);
	Array& operator=(const Array& other);
	T& operator[](unsigned int N);
	const T& operator[](unsigned int N) const;

	unsigned int size(void) const;
private:
    T*           _array;
    unsigned int _size;

};
#include "Array.tpp"
#endif /* ARRAY_HPP */