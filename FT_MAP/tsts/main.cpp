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


int main()
{

    std::vector<std::pair<char, int> > _v(10, std::pair<char, int>('l', 12));

    _v[0].first = 'k';
    _v[9].second = 23;


}
