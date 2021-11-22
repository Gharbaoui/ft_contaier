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

struct Base{};

struct A : public Base{
	int x;
};



int main()
{
	std::vector<std::pair<int, char> > _v;
	_v.push_back(std::make_pair(1, 'k'));
	_v.push_back(std::make_pair(3, 'k'));
	_v.push_back(std::make_pair(6, 'm'));

	std::map<int, char> mp(_v.begin(), _v.end());

	std::map<int, char>::iterator itr(mp.begin());

	itr++;
	itr++;
	std::cout << itr->first << std::endl;
	itr++;
	itr++;
	itr--;
	std::cout << itr->first << std::endl;
}
