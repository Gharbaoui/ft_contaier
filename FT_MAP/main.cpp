#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"

int main()
{
    std::vector<ft::pair<int, char> > _v(10);

    ft::map<int, char>  mp(_v.begin(), _v.end());
}
