#ifndef MAP_HPP
#define MAP_HPP
#include "pair.hpp"
#include "red-black.hpp"
namespace ft
{

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map{
	public:
		typedef	Key													key_type;
		typedef	T													mapped_type;
		typedef	ft::pair<const Key, T>								value_type;
		typedef	size_t												size_type;
		typedef	std::ptrdiff_t										difference_type;
		typedef	Compare												key_compare;
		typedef	Allocator											allocator_type;
		typedef	value_type&											reference;
		typedef	const value_type&									const_reference;
		typedef	RB_tree<value_type, key_compare,  allocator_type>	red_black_tree;

		class value_compare : public	ft::binary_function<value_type, value_type, bool>
		{
            friend class map;

			protected:
				value_compare( Compare c ) : comp(c) {}
				key_compare comp;
			public:
				bool operator()(const value_type& lhs, const value_type& rhs) const
				{
					return comp(lhs.first, rhs.first);
				}
		};

		// constructor
		map() {}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _cmp(comp), _mem(alloc) {}

		template< class InputIt >
		map(InputIt first, InputIt last,
     		const Compare& comp = Compare(),
     		const Allocator& alloc = Allocator()) : _mem(alloc), _cmp(comp)
		{
            while (first != last)
            {
                _rb_tree.insert(*first);
                ++first;
            }
		}

        void    remove_inter(const value_type &v)
        {
            _rb_tree.rb_delete(v);
        }
	private:
		allocator_type	_mem;
		key_compare		_cmp;
		red_black_tree	_rb_tree;

};

};


#endif
