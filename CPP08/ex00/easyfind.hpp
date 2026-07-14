
#ifndef EASYFIND_HPP
#define EASYFIND_HPP
#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T& container, int tofind)
{
	typename T::iterator it = std::find(container.begin(), container.end(), tofind);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}


#endif /* EASYFIND_HPP */