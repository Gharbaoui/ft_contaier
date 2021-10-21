#include <iostream>
#include "vector.hpp"
#include <vector>
#include "help.hpp"

int main()
{
	std::cout << "\033[1;32mclear  test\033[0m" << std::endl << std::endl;
	ft::vector<double> ft_vec(23, 56);
	std::vector<double> st_vec(23, 56);

/*	std::cout << "\033[1;36mbefore clear\033[0m" << std::endl;
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;
	std::cout << "\033[1;36mafter clear\033[0m" << std::endl;
	ft_vec.clear();
	st_vec.clear();
	std::cout << ft_vec << std::endl;
	std::cout << st_vec << std::endl;

	std::cout << "\033[1;32minsert with iterator and value test\033[0m" << std::endl << std::endl;
	std::cout << *ft_vec.insert(ft_vec.begin(), -998) << std::endl;
	std::cout << ft_vec << std::endl;
	std::cout << *st_vec.insert(st_vec.begin(), -998) << std::endl;
	std::cout << st_vec << std::endl;
	
	std::cout << "\033[1;32minsert with iterator , count and value test\033[0m" << std::endl << std::endl;*/
	ft_vec.insert(ft_vec.begin() + 89, 4 , -998);
	std::cout << ft_vec << std::endl;
	st_vec.insert(st_vec.begin() + 89, 4, -998);
	std::cout << st_vec << std::endl;


}
