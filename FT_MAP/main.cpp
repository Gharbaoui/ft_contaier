#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"
#include <stdlib.h>

int main()
{
    std::vector <std::pair<int, char> > _v;

    _v.push_back(std::make_pair(1, 'l'));
    _v.push_back(std::make_pair(2, 'g'));
    _v.push_back(std::make_pair(3, 'f'));

    std::map<int, char> mp(_v.begin(), _v.end());

    std::map<int, char>::iterator ib(mp.begin());


    --ib;
    ++ib;
    std::cout << ib->first << std::endl;

}
