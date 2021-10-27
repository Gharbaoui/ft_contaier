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
	std::cout << "\nsize: " << size << " capacity: " << v.capacity() << std::endl;
	return os;
}

template <typename T>
std::ostream	&operator<< (std::ostream &os, std::vector<T> &v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i){
		os << v[i] << " ";
	}
	std::cout << "\nsize: " << size << " capacity: " << v.capacity() << std::endl;
	return os;
}


class MEM{
	public:
		MEM() {ptr = nullptr;}
		MEM(const MEM &) {
			ptr = new float();
		}
		MEM&	operator=(const MEM&)
		{
			if (!ptr)
				ptr = new float();
			return *this;
		}
		~MEM() {delete ptr;}
	private:
		float *ptr;
};


int main()
{
	ft::vector<int> g(12, 34);
	ft::reverse_iterator<ft::vector<int>::iterator> k(g.rbegin());
	ft::reverse_iterator<ft::vector<int>::const_iterator> l(g.rbegin());

	std::reverse_iterator<std::vector<int>::iterator> mm;

	std::cout << (l - k) << std::endl;
}
