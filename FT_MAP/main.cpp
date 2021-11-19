#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"
#include <stdlib.h>

int main()
{
    int size = 10;
    std::vector<ft::pair<int, char> > _vp;
    std::vector<int> _keys{3505, 3681, 1046, 1707, 4148, 4901, 284, 237, 776, 4416};
    
    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        _vp.push_back(ft::make_pair(_keys[i], 32 + rand() % 50));
        std::cout << _vp[i].first << ", ";
    }
    std::cout << std::endl;
    ft::map<int, char> mp(_vp.begin(), _vp.end());


   mp.remove_intr(284); 



}
