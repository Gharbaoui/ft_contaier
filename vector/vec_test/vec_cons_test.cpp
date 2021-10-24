#include <iostream>
#include <vector>
#include "vector.hpp"
#include "help.hpp"

class A{
	public:
		~A(){std::cout << "destructor called" << std::endl;};
};


int main()
{
	std::cout << "\033[1;32mdefalut constructor test\033[0m" << std::endl << std::endl;
	ft::vector <int> ft_dc;
	std::vector <int> st_dc;
	std::cout << ft_dc << std::endl;
	std::cout << st_dc << std::endl;

	std::cout << "\033[1;32mparam  constructor test\033[0m" << std::endl << std::endl;

	ft::vector <int> ft_pc(12);
	std::vector <int> st_pc(12);
	std::cout << ft_pc << std::endl;
	std::cout << st_pc << std::endl;

	std::cout << "\033[1;32mcopy constrctor test\033[0m" << std::endl << std::endl;
	ft::vector <int> ft_cc(ft_pc);
	std::vector <int> st_cc(st_pc);
	std::cout << ft_cc << std::endl;
	std::cout << st_cc << std::endl;

	std::cout << "\033[1;32mallocator constrctor test\033[0m" << std::endl << std::endl;
	std::allocator<int> alloc;
	ft::vector <int> ft_ac(alloc);
	std::vector <int> st_ac(alloc);
	std::cout << ft_ac << std::endl;
	std::cout << st_ac << std::endl;


	std::cout << "\033[1;32mparam with value constrctor test\033[0m" << std::endl << std::endl;
	ft::vector <int> ft_vc(12, 34);
	std::vector <int> st_vc(12, 34);
	std::cout << ft_vc << std::endl;
	std::cout << st_vc << std::endl;
	
	std::cout << "\033[1;32mparam with value and allocator  constrctor test\033[0m" << std::endl << std::endl;
	ft::vector <int> ft_vac(12, 89, alloc);
	std::vector <int> st_vac(12, 89, alloc);
	std::cout << ft_vac << std::endl;
	std::cout << st_vac << std::endl;
	
	
	std::cout << "\033[1;32miterator constrctor test\033[0m" << std::endl << std::endl;
	ft::vector <int> ft_ic(ft_vac.begin(), ft_vac.end());
	std::vector <int> st_ic(st_vac.begin(), st_vac.end());
	std::cout << ft_ic << std::endl;
	std::cout << st_ic << std::endl;
	
	std::cout << "\033[1;32massigment operator test\033[0m" << std::endl << std::endl;
	ft_dc = ft_vac;
	st_dc = st_vac;
	std::cout << ft_dc << std::endl;
	std::cout << st_dc << std::endl;
	
	std::cout << "\033[1;32mdestructor  test\033[0m" << std::endl << std::endl;
	{
		A a;
		{
			std::cout << "ft vector" << std::endl;
			ft::vector<A> ft_d(3, a);
		}
		{
			std::cout << "std vector" << std::endl;
			std::vector<A> st_d(3, a);
		}
		std::cout << "object a is done" << std::endl;
	}
	
	std::cout << "\033[1;32massign with count\033[0m" << std::endl << std::endl;
	ft_dc.assign(23, -9800);
	st_dc.assign(23, -9800);
	std::cout << ft_dc << std::endl;
	std::cout << st_dc << std::endl;
	
	std::cout << "\033[1;32massign with iterator\033[0m" << std::endl << std::endl;
	ft_dc.assign(ft_vac.begin(),ft_vac.end());
	st_dc.assign(st_vac.begin(), st_vac.end());
	std::cout << ft_dc << std::endl;
	std::cout << st_dc << std::endl;

	std::cout << "\033[1;32mget allocator test\033[0m" << std::endl << std::endl;
	std::allocator<int> a1 = ft_dc.get_allocator();
	std::allocator<int> a2 = st_dc.get_allocator();
}
