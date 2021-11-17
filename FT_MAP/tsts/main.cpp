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
    int size1 = 10;
    std::vector<std::pair<int, char> > _v1;
    srand(time (NULL));

    for (int i = 0; i < size1; ++i)
        _v1.push_back(std::pair<int, char>(rand() % 1000, 32 + rand() % 50));
    int size2 = 10;

    std::vector<std::pair<int, char> > _v2;
    srand(time (NULL) * time(NULL));

    for (int i = 0; i < size2; ++i)
        _v2.push_back(std::pair<int, char>(rand() % 1000, 32 + rand() % 50));
    
    std::map<int, char> mp1(_v1.begin(), _v1.end());
    std::map<int, char> mp2(_v2.begin(), _v2.end());

    
    std::map<int, char>::iterator itr(mp1.begin());


    ++itr;

}
