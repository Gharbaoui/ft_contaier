#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"
#include <stdlib.h>


int main()
{
	int size = 200;

    std::vector <ft::pair<int, char> > _v/*{ft::make_pair(5, 'h'), ft::make_pair(7, 'k'), ft::make_pair(0, 'h'), ft::make_pair(1, 'k'), ft::make_pair(3, 'h'), ft::make_pair(55, 'k'), ft::make_pair(9, 'h'), ft::make_pair(8, 'k'), ft::make_pair(87, 'k')}*/;

	srand(time(NULL));
	for (int i = 0; i < size; ++i)
	{
		int v = rand() % 1000;
		_v.push_back(ft::make_pair(v, 32 + rand() % 55));
		std::cout << v << ", ";
	}

	std::cout << std::endl;


	ft::map<int, char> mp(_v.begin(), _v.end());


	ft::map<int, char>::iterator i(mp.begin());

	for (; i != mp.end(); ++i)	
		std::cout << i->first  << ": " << i->second << std::endl;
}
