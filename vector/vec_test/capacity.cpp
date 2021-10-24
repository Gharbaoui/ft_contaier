#include <iostream>
#include "vector.hpp"
#include <vector>
#include "help.hpp"

int main()
{
	std::cout << "\033[1;32mempty  test\033[0m" << std::endl << std::endl;
	ft::vector <int> f_v;
	std::vector <int> s_v;

	std::cout << f_v.empty() << std::endl;
	std::cout << s_v.empty() << std::endl;
	f_v.push_back(12);
	s_v.push_back(12);
	std::cout << f_v.empty() << std::endl;
	std::cout << s_v.empty() << std::endl;

	std::cout << "\033[1;32msize  test\033[0m" << std::endl << std::endl;
	std::cout << f_v.size() << std::endl;
	std::cout << s_v.size() << std::endl;
	std::cout << "\033[1;40madd one elment\033[0m" << std::endl;
	f_v.push_back(12);
	s_v.push_back(12);
	std::cout << f_v.size() << std::endl;
	std::cout << s_v.size() << std::endl;
	std::cout << "\033[1;40mremove both elment\033[0m" << std::endl;
	f_v.pop_back();
	f_v.pop_back();
	s_v.pop_back();
	s_v.pop_back();
	std::cout << f_v.size() << std::endl;
	std::cout << s_v.size() << std::endl;

	std::cout << "\033[1;40mmax_size\033[0m" << std::endl;
	std::cout << f_v.max_size() << std::endl;
	std::cout << s_v.max_size() << std::endl;

	std::cout << "\033[1;32mreserve\033[0m" << std::endl;
	std::cout << "\033[1;39mft before reserve\033[0m" << std::endl;
	std::cout << "size: " << f_v.size() << " capacity: " << f_v.capacity() << std::endl;
	f_v.reserve(100);
	std::cout << "\033[1;39mft after reserve\033[0m" << std::endl;
	std::cout << "size: " << f_v.size() << " capacity: " << f_v.capacity() << std::endl;
	
	std::cout << "\033[1;39mstd before reserve\033[0m" << std::endl;
	std::cout << "size: " << s_v.size() << " capacity: " << s_v.capacity() << std::endl;
	s_v.reserve(100);
	std::cout << "\033[1;39mstd after reserve\033[0m" << std::endl;
	std::cout << "size: " << s_v.size() << " capacity: " << s_v.capacity() << std::endl;
	
	std::cout << "\033[1;32mshrink_to_fit  test\033[0m" << std::endl << std::endl;
	// fill with some numbers
	for (int i = 0; i < 10; ++i)
	{
		f_v.push_back(i + 1);
		s_v.push_back(i + 1);
	}

	std::cout << "\033[1;39mft before shrink_to_fit\033[0m" << std::endl;
	std::cout << f_v << std::endl;
	std::cout << "\033[1;39mft after shrink_to_fit\033[0m" << std::endl;
	f_v.shrink_to_fit();
	std::cout << f_v << std::endl;
	
	std::cout << "\033[1;39mstd before shrink_to_fit\033[0m" << std::endl;
	std::cout << s_v << std::endl;
	std::cout << "\033[1;39mstd after shrink_to_fit\033[0m" << std::endl;
	s_v.shrink_to_fit();
	std::cout << s_v << std::endl;
}
