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
    ft::vector<std::string>    ft_v1(1e6, "string2");
	ft::vector<std::string>    ft_v2(1e4, "string2");
	ft_v2.assign(ft_v1.begin(), ft_v1.end());
}
