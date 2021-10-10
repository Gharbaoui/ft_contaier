#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream> // remove later

#include <memory>
#include <stdexcept>
namespace ft{

#include "vector-class.hpp"
#include "member-functions.hpp"
#include "element-access.hpp"
#include "capacity.hpp"
#include "modifiers.hpp"

template <typename T, typename Alloc>
void	vector<T, Alloc>::range_destroy(int start, int end, int cap)
{
	for (int i = start; i < end; ++i)
		mem_manager.destroy(_arr + i);
	mem_manager.deallocate(_arr , cap);
}

}
#endif
