#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <list>
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


class A{
	public:
		A(){
			std::cout << "called" << std::endl;
			val = new int();
		};
		A(const A &cp)
		{
	//		std::cout << "copy called" << std::endl;
			val = new int();
		}
		A	&operator=(const A &rhs)
		{
			val = new int(*rhs.val);
			std::cout << "assigment called" << std::endl;
			return *this;
		}
		~A()
		{
			std::cout << "destuctor" << std::endl;
			delete val;
		}
		int *val;
};


template <typename Iter>
typename std::enable_if <std::is_convertible<typename std::iterator_traits<Iter>::iterator_category, std::input_iterator_tag>::value>::type
f(Iter beg, Iter end)
{
	for (; beg != end; ++beg)
		std::cout << *beg << " ";
	std::cout << std::endl;
}

void	 f(int val, int other) {
	std::cout << "normal" << std::endl;
}


int main()
{
	std::vector<int> h(1000000, 34);

	h.push_back(45);
	std::cout << h.capacity() << std::endl;
}
