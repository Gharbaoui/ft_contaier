#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"


int main()
{
	std::vector<ft::pair<int, char> > _v1;
	_v1.push_back(ft::make_pair(1, 'e'));
	_v1.push_back(ft::make_pair(2, 'f'));

	std::vector<ft::pair<int, char> > _v2;
	_v2.push_back(ft::make_pair(3, 'E'));
	_v2.push_back(ft::make_pair(4, 'F'));

/*	ft::map<int, char> mp1(_v1.begin(), _v1.end());
	ft::map<int, char> mp2(_v2.begin(), _v2.end());

	mp1.swap(mp2);
	ft::map<int, char>::iterator i1b(mp1.begin());
	ft::map<int, char>::iterator i1e(mp1.end());


	ft::map<int, char>::iterator i2b(mp2.begin());
	ft::map<int, char>::iterator i2e(mp2.end());


	std::cout << "map 1" << std::endl;
	for (; i1b != i1e; ++i1b)
		std::cout << i1b->first << ": " << i1b->second << std::endl;
	std::cout << "map 2" << std::endl;
	for (; i2b != i2e; ++i2b)
		std::cout << i2b->first << ": " << i2b->second << std::endl;


	std::cout << mp2.count(2) << std::endl;*/

	ft::map<int, char> const m1(_v1.begin(), _v1.end());
	ft::map<int, char>::const_iterator i = m1.find(2);


	std::cout << i->first << ": " << i->second << std::endl;



}
