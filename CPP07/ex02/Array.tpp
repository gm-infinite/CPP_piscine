
#ifndef ARRAY_TPP
#define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _array(NULL), _size(0)
{ }

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n)
{ }

template <typename T>
Array<T>::Array(const Array& other)
{
	this->_size = other._size;
	this->_array = new T[other._size]();
	for (unsigned int i = 0; i < other._size; ++i)
		(*this)[i] = other[i];

}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		T* newArray = new T[other._size]();
		for (unsigned int i = 0; i < other._size; ++i)
			newArray[i] = other[i];
		delete[] this->_array;
		this->_array = newArray;
		this->_size = other._size;
	}
	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int N)
{
	if (N >= this->_size)
		throw std::out_of_range("Array index out of bounds");
	return (this->_array)[N];
}

template <typename T>
const T& Array<T>::operator[](unsigned int N) const
{
	if (N >= this->_size)
		throw std::out_of_range("Array index out of bounds");
	return (this->_array)[N];
}
template <typename T>
unsigned int Array<T>::size(void) const
{
	return this->_size;
}

template <typename T>
Array<T>::~Array(void)
{
    delete[] this->_array;
}



#endif /* ARRAY_TPP */