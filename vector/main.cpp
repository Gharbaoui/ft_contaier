#include "vector.hpp"
#include <type_traits>
#include <vector>
#include <list>

template <typename T>
std::ostream	&operator<< (std::ostream &os, ft::vector<T> &v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i){
		os << v[i] << " ";
	}
	return os;
}

int main()
{

	int y;
	std:: cin >> y;
}
