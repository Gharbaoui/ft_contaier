#include <vector>
#include "vector.hpp"
#include <iostream>

int main()
{
	ft::vector <long> f_vec(10, 78);
	std::vector <long> s_vec(10, 78);
	
	ft::vector<long>::reverse_iterator f_di(f_vec.rbegin());
	std::vector<long>::reverse_iterator s_di(s_vec.rbegin());
	ft::vector<long>::const_reverse_iterator f_cdi(f_vec.rbegin());
	std::vector<long>::const_reverse_iterator s_cdi(s_vec.rbegin());

	std::cout << "\033[1;32m+= operator test\033[0m" << std::endl << std::endl;
	f_vec[f_vec.size() - 4] = -96;
	s_vec[s_vec.size() - 4] = -96;
	f_di += 3;
	s_di += 3;
	f_cdi += 3;
	s_cdi += 3;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;
	
	std::cout << "\033[1;32m-= operator test\033[0m" << std::endl << std::endl;
	f_vec[f_vec.size() - 1] = -95000;
	s_vec[f_vec.size() - 1] = -95000;
	f_di -= 3;
	s_di -= 3;
	f_cdi -= 3;
	s_cdi -= 3;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;


	std::cout << "\033[1;32m(iter + n) operator test\033[0m" << std::endl << std::endl;	
	f_vec[f_vec.size() - 6] = 32;
	s_vec[s_vec.size() - 6] = 32;
	f_di = f_di + 5;
	s_di = s_di + 5;
	f_cdi = f_cdi + 5;
	s_cdi = s_cdi + 5;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;

	std::cout << "\033[1;32m(n + iter)operator test\033[0m" << std::endl << std::endl;	
	f_vec[f_vec.size() - 8] = -32; // 7 because iterators are alreday pointing to 5 and add 2 down
	s_vec[s_vec.size() - 8] = -32;
	f_di = 2 + f_di;
	s_di = 2 + s_di;
	f_cdi = 2 + f_cdi;
	s_cdi = 2 + s_cdi;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;


	std::cout << "\033[1;32m(iter - n) operator test\033[0m" << std::endl << std::endl;	
	f_di = f_di - 7; // go back to 0 element
	s_di = s_di - 7;
	f_cdi = f_cdi - 7;
	s_cdi = s_cdi - 7;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;
	
	std::cout << "\033[1;32m difference_type  test\033[0m" << std::endl << std::endl;	
	f_cdi = f_vec.rend();
	s_cdi = s_vec.rend();
	std::cout << "F: " << (f_cdi - f_di) << std::endl;
	std::cout << "S: " << (s_cdi - s_di) << std::endl;
	
	std::cout << "\033[1;32m[] operator  test\033[0m" << std::endl << std::endl;	

	f_di[3] = 56;
	s_di[3] = 56;
	std::cout << "F iterator: " << f_di[3] << std::endl;
	std::cout << "S iterator: " << s_di[3] << std::endl;

	std::cout << "\033[1;32m < and > operator  test\033[0m" << std::endl << std::endl;
	std::cout << "F iterator: " << (f_di < f_cdi) << std::endl;
	std::cout << "F iterator: " << (f_di > f_cdi) << std::endl;
	std::cout << "S iterator: " << (s_di < s_cdi) << std::endl;
	std::cout << "S iterator: " << (s_di > s_cdi) << std::endl;
	
	std::cout << "\033[1;32m <= and >= operator  test\033[0m" << std::endl << std::endl;
	f_cdi = f_di;
	--f_cdi;
	s_cdi = s_di;
	--s_cdi;
	std::cout << "F iterator: " << (f_di <= f_cdi) << std::endl;
	std::cout << "F iterator: " << (f_di >= f_cdi) << std::endl;
	std::cout << "S iterator: " << (s_di <= s_cdi) << std::endl;
	std::cout << "S iterator: " << (s_di >= s_cdi) << std::endl;

	std::cout << "\033[1;32m != and == operator  test\033[0m" << std::endl << std::endl;
	++f_cdi;
	++s_cdi;
	std::cout << "F iterator: " << (f_di == f_cdi) << std::endl;
	std::cout << "F iterator: " << (f_di != f_cdi) << std::endl;
	std::cout << "S iterator: " << (s_di == s_cdi) << std::endl;
	std::cout << "S iterator: " << (s_di != s_cdi) << std::endl;

	std::cout << "\033[1;32m print using iterator test\033[0m" << std::endl << std::endl;

	f_cdi = f_vec.rend();
	f_di = f_vec.rbegin();
	s_di = s_vec.rbegin();

	srand(time(NULL));
	for (; f_di != f_cdi; ++f_di)
	{
		*f_di = rand() % 100;
		*s_di = *f_di;
		++s_di;
	}

	std::cout << "ft iterator" << std::endl;
	f_cdi = f_vec.rbegin();
	f_di = f_vec.rend();
	for (;f_cdi != f_di; ++f_cdi)
		std::cout << *f_cdi << " ";
	std::cout << std::endl;
	std::cout << "std iterator" << std::endl;
	s_cdi = s_vec.rbegin();
	s_di = s_vec.rend();
	for (;s_cdi != s_di; ++s_cdi)
		std::cout << *s_cdi << " ";
	std::cout << std::endl;

}
