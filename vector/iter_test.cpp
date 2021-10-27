#include <vector>
#include "vector.hpp"
#include <iostream>

int main()
{
	ft::vector <long> f_vec(10, 78);
	std::vector <long> s_vec(10, 78);
	
	ft::vector<long>::iterator f_di(f_vec.begin());
	std::vector<long>::iterator s_di(s_vec.begin());
	ft::vector<long>::const_iterator f_cdi(f_vec.begin());
	std::vector<long>::const_iterator s_cdi(s_vec.begin());

	std::cout << "\033[1;32m+= operator test\033[0m" << std::endl << std::endl;
	f_vec[3] = -95;
	s_vec[3] = -95;
	f_di += 3;
	s_di += 3;
	f_cdi += 3;
	s_cdi += 3;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;
	
	std::cout << "\033[1;32m-= operator test\033[0m" << std::endl << std::endl;
	f_vec[0] = -95000;
	s_vec[0] = -95000;
	f_di -= 3;
	s_di -= 3;
	f_cdi -= 3;
	s_cdi -= 3;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;


	std::cout << "\033[1;32m(iter + n) operator test\033[0m" << std::endl << std::endl;	
	f_vec[5] = 32;
	s_vec[5] = 32;
	f_di = f_di + 5;
	s_di = s_di + 5;
	f_cdi = f_cdi + 5;
	s_cdi = s_cdi + 5;
	std::cout << "f iterator: " << *f_di << std::endl;
	std::cout << "s iterator: " << *s_di << std::endl;
	std::cout << "f const iterator: " << *f_cdi << std::endl;
	std::cout << "s const iterator: " << *s_cdi << std::endl;
	
	std::cout << "\033[1;32m(n + iter)operator test\033[0m" << std::endl << std::endl;	
	f_vec[7] = -32; // 7 because iterators are alreday pointing to 5 and add 2 down
	s_vec[7] = -32;
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
	f_cdi = f_vec.end();
	s_cdi = s_vec.end();
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

	f_cdi = f_vec.end();
	f_di = f_vec.begin();
	s_di = s_vec.begin();

	srand(time(NULL));
	for (; f_di != f_cdi; ++f_di)
	{
		*f_di = rand() % 100;
		*s_di = *f_di;
		++s_di;
	}

	std::cout << "ft iterator" << std::endl;
	f_cdi = f_vec.begin();
	f_di = f_vec.end();
	for (;f_cdi != f_di; ++f_cdi)
		std::cout << *f_cdi << " ";
	std::cout << std::endl;
	std::cout << "std iterator" << std::endl;
	s_cdi = s_vec.begin();
	s_di = s_vec.end();
	for (;s_cdi != s_di; ++s_cdi)
		std::cout << *s_cdi << " ";
	std::cout << std::endl;

}
