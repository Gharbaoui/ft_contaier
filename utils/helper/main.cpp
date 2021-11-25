#include <iostream>
#include <vector>
#include "simple.hpp"
#include <algorithm>
#include <functional>

int main()
{
    std::vector<int> v1, v2;

    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(4);

    v2.push_back(10);
    v2.push_back(20);
    v2.push_back(30);
    //v2.push_back(4);

    std::cout <<
    std::lexicographical_compare(v2.begin(), v2.end(), v1.begin(), v1.end(), std::less<>())

    << std::endl;
}

