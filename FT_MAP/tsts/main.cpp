#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <memory>


template <typename T>
class MyAllocator : public std::allocator<T>
{
    public:
        typedef size_t size_type;
        typedef T* pointer;
        typedef const T* const_pointer;

        pointer allocate(size_type n)
        {
            std::cout << "good" << std::endl;
            return std::allocator<T>::allocate(n);
        }
};

void    map_display(const std::map<int, char> &mp)
{
    for (auto itr = mp.begin(); itr != mp.end(); ++itr)
       std::cout << itr->first << ": " << itr->second << std::endl;
}

int main()
{
    std::vector<std::pair<int, char> > _v;

    _v.push_back(std::pair<int, char>(12, 'l'));

    std::map<int, char> mp1(_v.begin(), _v.end());
    std::map<int, char> mp2(_v.begin(), _v.end());

    std::map<int, char>::iterator it1(mp1.begin());
    std::map<int, char>::iterator it2(mp1.begin());

    std::cout << (it1 == it2) << std::endl;
}
