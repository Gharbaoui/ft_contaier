#include "vector.hpp"
#include <type_traits>
#include <vector>
#include <list>

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
			val = new int();
		}
		A(const A &cp)
		{
			//std::cout << "copy  called" << std::endl;
			val = new int(*cp.val);
		}
		A(int h){
			val = new int(h);
		}
		~A(){
			std::cout << "destructor called" << std::endl;
			delete val;
		};
	private:
		int *val;
};


int main()
{
	ft::vector<A> g(12, A());

	g.resize(11);



	int y;

	std:: cin >> y;

}
