#ifndef MAP_HPP
#define MAP_HPP

#include  <stdexcept>
#include "pair.hpp"
#include "./RB_TREE/red-black.hpp"
#include "../utils/iterator-traits/iterator-traits.hpp"
#include "../utils/iterator-traits/map_iterator.hpp"

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
		typedef	Key													        key_type;
		typedef	T													        mapped_type;
		typedef	ft::pair<const Key, T>								        value_type;
		typedef	size_t												        size_type;
		typedef	std::ptrdiff_t										        difference_type;
		typedef	Compare												        key_compare;
		typedef	Allocator											        allocator_type;
		typedef	value_type&											        reference;
		typedef	const value_type&									        const_reference;
        typedef RB_manager<value_type, key_compare, key_type, allocator_type>   rb_tree;
        typedef rb_iterator<value_type>                                      iterator;
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
        ~map () {}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
        : _cmp(comp), _mem(alloc) {}

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

        allocator_type get_allocator() const {return _mem;}


	private:
		allocator_type	_mem;
		key_compare		_cmp;
        rb_tree         _rb_tree;

};

};


#endif
