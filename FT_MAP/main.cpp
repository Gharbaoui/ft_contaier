#include <iostream>
#include <map>
#include <vector>
#include "map.hpp"
#include "pair.hpp"

int main()
{
	{
		ft::map<int, char> my_m;
		ft::map<int, char>::iterator my_it, my_it1/*, tmp*/;

		for (int i = 0; i < 10; ++i)
			my_m.insert(ft::make_pair(i, static_cast<char>(i + 97)));

		my_it = my_it1;
	//	my_it1 = ++(my_m.begin());
	}
	std::cout << "test for leak" << std::endl;
	int y;
	std::cin >> y;
}
