#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"
#include <stdlib.h>


int main()
{
	std::vector<ft::pair<int, char> > _v;
	_v.push_back(ft::make_pair(1, 'e'));
	_v.push_back(ft::make_pair(2, 'f'));
	_v.push_back(ft::make_pair(3, 'b'));
	_v.push_back(ft::make_pair(4, 'b'));
	_v.push_back(ft::make_pair(5, 'e'));
	_v.push_back(ft::make_pair(6, 'f'));
	_v.push_back(ft::make_pair(7, 'b'));
	_v.push_back(ft::make_pair(48, 'b'));

	ft::map<int, char> mp(_v.begin(), _v.end());
	ft::map<int, char>::iterator itr(mp.begin());
	ft::map<int, char>::const_iterator citr;


    std::map<int, char>::iterator p;
    std::map<int, char>::const_iterator cp;

    p == cp;
}
