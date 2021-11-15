#include <iostream>
#include <map>

class A{
	public:
		A() {}
		A(int h) : l(h) {}
		int l;	
};


bool	operator>(const A &lhs, const A &rhs)
{
	return lhs.l > rhs.l;
}


template <typename T, typename Comp>
class MAP
{
	public:
		void	test()
		{
			std::cout << _cmp(arr[0], arr[1]) << std::endl;
		}
	private:
		T arr[10];
		Comp _cmp;
};


int main()
{
	MAP<A, std::greater<A> > p;

	p.test();

}
