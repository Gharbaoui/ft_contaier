#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"
#include <stdlib.h>

int main()
{
    int size = 20;
    std::vector<ft::pair<int, char> > _v;
    std::vector<int> _keys{446, 491, 443, 332, 813, 736, 633, 167, 442, 310, 36, 324, 455, 877, 144, 244, 458, 676, 89, 71};


    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        _v.push_back(ft::pair<int, char>(_keys[i], 32 + rand() % 50));
        std::cout << _v[i].first << ", ";
    }

    std::cout << std::endl;
    ft::map<int, char>  mp(_v.begin(), _v.end());

    mp.remove_inter(_v[5]);
}
