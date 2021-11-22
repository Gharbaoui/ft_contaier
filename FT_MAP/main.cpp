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

	ft::map<int, char> mp(_v.begin(), _v.end());
	ft::map<int, char>::reverse_iterator itr(mp.rend());


	--itr;
	--itr;
	--itr;
	--itr;
}
