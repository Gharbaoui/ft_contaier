#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <list>
#include <forward_list>
#include <iterator>
#include <type_traits>
#include "list.hpp"

template <typename T>
std::ostream	&operator<<(std::ostream &os, std::vector<T> v)
{
	int size;
	size = v.size();
	for (int i = 0; i < size; ++i)
	{
		os << v[i] << " ";
	}
	os  << std::endl;
	os << "size: " << v.size() << " capacity: " << v.capacity();
	return os;
}


namespace my{

	struct	input_iterator_tag{}; // read only
	struct	output_iterator_tag{}; // write only
	struct	forward_iterator_tag : input_iterator_tag{}; // read write advance only
	struct	bidirectional_iterator_tag : forward_iterator_tag {}; // added go boack --
	struct 	random_access_iterator_tag : bidirectional_iterator_tag {}; // add [] operator

	template <typename T> // T => iterator
	struct iterator_traits{
		typedef	typename	T::value_type			value_type;
		typedef	typename	T::difference_type		difference_type;
		typedef	typename	T::iterator_category	iterator_category;
		typedef	typename	T::pointer				pointer;
		typedef	typename	T::reference			reference;
	};
};


class A{
	A() {
	
	}
};

int main()
{
	std::vector<int> f(4);

	std::cout << f.capacity() << std::endl;
	f.insert(f.begin(), 1, 2);
	std::cout << f.capacity() << std::endl;
}
