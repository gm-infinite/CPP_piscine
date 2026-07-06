
#ifndef ITER_HPP
#define ITER_HPP


template <typename T, typename F>
void iter(T* addr, const int size, F func)
{
	for (int i = 0; i < size; i++)
	{
		func(addr[i]);
	}
}

#endif /* ITER_HPP */