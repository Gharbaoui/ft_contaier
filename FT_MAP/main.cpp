#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"

int main()
{
	std::vector<std::pair<char, int> > _v(1, std::make_pair('l', 45));


	std::map<char, int> _m(_v.begin(), _v.end());


	for (int i = 0; i < 1; ++i)
		std::cout << _m[i] << std::endl;

}
