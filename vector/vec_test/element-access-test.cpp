#include <iostream>
#include "vector.hpp"
#include <vector>
#include "help.hpp"


int main()
{
	std::cout << "\033[1;32mat and [] operator test\033[0m" << std::endl << std::endl;
	ft::vector<float> fat_t(12, 34);
	std::vector<float> sat_t(12, 34);
	fat_t[3] = -785;
	sat_t[3] = -785;
	std::cout << fat_t.at(3) << std::endl;
	std::cout << sat_t.at(3) << std::endl;
	
	std::cout << "\033[1;32mfront test\033[0m" << std::endl << std::endl;
	fat_t[0] = 888;
	sat_t[0] = 888;
	std::cout << fat_t.front() << std::endl;
	std::cout << sat_t.front() << std::endl;

	
	std::cout << "\033[1;32mback test\033[0m" << std::endl << std::endl;
	fat_t[fat_t.size() - 1] = 45;
	sat_t[sat_t.size() - 1] = 45;
	std::cout << fat_t.back() << std::endl;
	std::cout << sat_t.back() << std::endl;


	std::cout << "\033[1;32mdata test\033[0m" << std::endl << std::endl;
	float *under = fat_t.data();
	for (int i = 0; i < fat_t.size(); ++i)
		std::cout << under[i] << " ";
	std::cout << std::endl;
	under = sat_t.data();
	for (int i = 0; i < sat_t.size(); ++i)
		std::cout << under[i] << " ";
	std::cout << std::endl;
}
