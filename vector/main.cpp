#include "vector.hpp"
/// need to look at construct that takes 33 param 
template <typename T>
std::ostream	&operator<< (std::ostream &os, ft::vector<T> &v)
{
	int size = v.size();

	for (int i = 0; i < size; ++i){
		os << v[i] << " ";
	}
	return os;
}

class	A{
	public:
		A(){
			std::cout << "constructor" << std::endl;
		}
		~A(){
			std::cout << "destructor called" << std::endl;
		};
};

int main()
{
	ft::vector<int> h(9, 34);
	ft::vector<int> c;

	c = h;
	c[0] = 89;
	std::cout << h << std::endl;
	std::cout << c << std::endl;
}
