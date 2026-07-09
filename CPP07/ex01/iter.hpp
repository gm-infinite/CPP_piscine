
#ifndef ITER_HPP
#define ITER_HPP


template <typename T, typename F>
void iter(T* addr, const unsigned int size, F func)
{
	for (unsigned int i = 0; i < size; i++)
	{
		func(addr[i]);
	}
}

#endif /* ITER_HPP */