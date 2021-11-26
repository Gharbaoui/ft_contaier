#ifndef set_HPP
#define set_HPP

#include  <stdexcept>
#include <unistd.h>
#include  <utility>
#include  <memory>
#include "../utils/helper/pair.hpp"
#include "../utils/helper/simple.hpp"
#include "./setRB/red-black.hpp"
#include "../utils/iterator-traits/iterator-traits.hpp"
#include "../utils/iterator-traits/iterators.hpp"
#include "../utils/iterator-traits/set_iterator.hpp"

namespace ft
{

template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
class set{
	public:
		typedef	Key																				key_type;
		typedef	Key																				value_type;
		typedef	size_t																			size_type;
		typedef	std::ptrdiff_t																	difference_type;
		typedef	Compare																			key_compare;
		typedef	Compare																			value_compare;
		typedef	Allocator																		allocator_type;
		typedef	value_type&																		reference;
		typedef	const value_type&																const_reference;
        typedef RB_manager<value_type, key_compare, key_type, allocator_type>					rb_tree;
        typedef rb_iterator<value_type, value_type&, value_type*, allocator_type>				iterator;
        typedef rb_iterator<value_type, value_type const&, value_type const*, allocator_type>	const_iterator;
		typedef	ft::reverse_iterator<iterator>													reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>									        const_reverse_iterator;
		typedef	RB_node<value_type>																node;


		// constructor
		set() : _rb_tree() {}
        ~set () {clear();}
		explicit set(const Compare& comp, const Allocator& alloc = Allocator())
        : _mem(alloc), _cmp(comp), _rb_tree() {}

		template< class InputIt >
		set(InputIt first, InputIt last,
     		const Compare& comp = Compare(),
     		const Allocator& alloc = Allocator()) : _mem(alloc), _cmp(comp)
		{
			bool	was_here;
            while (first != last)
            {
                _rb_tree.insert(*first, was_here);
                ++first;
            }
		}
		
		set(const set &cp)
		{
			insert(cp.begin(), cp.end());
		}

		set& operator=(const set& other)
		{
			if (this != &other)
			{
				if (size())
					clear();
				insert(other.begin(), other.end());
			}
			return *this;
		}

        allocator_type get_allocator() const {return _mem;}

		// iterator functions
		iterator	begin()
		{
			// if current is null in his place put last node
			return iterator(_rb_tree.left_most(), _rb_tree.get_last_node(), _rb_tree.right_most());
		}

		iterator	end()
		{
			return iterator(_rb_tree.get_last_node(), _rb_tree.get_last_node(), _rb_tree.right_most());
		}
		
		const_iterator	begin() const
		{
			return const_iterator(_rb_tree.left_most(), _rb_tree.get_last_node(), _rb_tree.right_most());
		}

		const_iterator	end() const
		{
			return const_iterator(_rb_tree.get_last_node(), _rb_tree.get_last_node(), _rb_tree.right_most());
		}

        reverse_iterator    rbegin()
        {
            return reverse_iterator(end());
        }

        reverse_iterator    rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator    rbegin() const
        {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator    rend() const
        {
            return const_reverse_iterator(begin());
        }

		bool empty() const {return _rb_tree.empty();}
		size_type size() const {return _rb_tree.get_size();}
		size_type max_size() const {return _mem.max_size();}
		ft::pair<iterator,bool> insert (const value_type& val)
		{
			bool was_here;
			node *cu = _rb_tree.insert(val, was_here);
			return ft::make_pair(iterator(cu, _rb_tree.get_last_node(), _rb_tree.right_most()), !was_here);
		}

		iterator insert(iterator hint, const value_type& value)
		{
			bool was;
			(void)hint;
			node *cu = _rb_tree.insert(value, was);
			return iterator(cu, _rb_tree.get_last_node(), _rb_tree.right_most());

		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			bool was;
			while (first != last)
			{
				_rb_tree.insert(*first, was);
				++first;
			}
		}
		
		void erase (iterator position)
		{
			_rb_tree.remove_node(key_type(), position.get_current());
		}

		size_type erase (const key_type& k)
		{
			return _rb_tree.remove_node(k);
		}

		void erase (iterator first, iterator last)
		{
			key_type k;
			// first++ should be not ++first
			// so for example
			// you delete at first and delete will change what first points to and set to null inside
			// and then you do ++first and ++operator depends on current to get to next element
			// so no way to get next elem
			// but when you do ++first you interly move curent to next
			// and return old one that will be removed
			while (first != last)
				_rb_tree.remove_node(k, (first++).get_current());
		}

		void clear()
		{
			if (size())
				erase(begin(), end());
		}

		void swap( set& other )
		{
			_rb_tree.swap_rb_manager(other._rb_tree);
		}

		size_type count(const Key& key) const
		{
			node *n = _rb_tree.find(key);
			return n ? 1 : 0;
		}

		iterator find(const Key& key)
		{
			node *n = _rb_tree.find(key);
			if (!n)
				n = _rb_tree.get_last_node();
			return iterator(n, _rb_tree.get_last_node(), _rb_tree.right_most());
		}
		
		const_iterator find( const Key& key ) const
		{
			node *n = _rb_tree.find(key);
			if (!n)
				n = _rb_tree.get_last_node();
			return const_iterator(n, _rb_tree.get_last_node(), _rb_tree.right_most());
		}

		iterator lower_bound(const Key& key)
		{
			// return iterator to obj that has key
			// and if not found return what comes after next
			// and if key is bigger than last elm I return last_node which is mine
			return iterator(_rb_tree.lower_bound(key), _rb_tree.get_last_node(), _rb_tree.right_most());
		}

		const_iterator lower_bound( const Key& key ) const
		{
			return const_iterator(_rb_tree.lower_bound(key), _rb_tree.get_last_node(), _rb_tree.right_most());
		}

		iterator upper_bound( const Key& key )
		{
			// return iterator to first greater elm after key
			//so this to be true iter should be greater than key
			return iterator(_rb_tree.upper_bound(key), _rb_tree.get_last_node(), _rb_tree.right_most());
		}

		const_iterator upper_bound( const Key& key ) const
		{
			// return iterator to first greater elm after key
			//so this to be true iter should be greater than key
			return const_iterator(_rb_tree.upper_bound(key), _rb_tree.get_last_node(), _rb_tree.right_most());
		}
		
		key_compare key_comp() const
		{
			return _cmp;
		}

		value_compare value_comp() const
		{
			return value_compare();
		}
		
		ft::pair<iterator,iterator> equal_range(const Key& key)
		{
            Key k;
			iterator _beg(lower_bound(key));
			iterator _end(_beg);

			k = *_beg;
			if (!_cmp(k, key) && !_cmp(key, k))
				++_end;
			return ft::make_pair(_beg, _end);
		}

		ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const
		{
            Key k;
			const_iterator _beg(lower_bound(key));
			const_iterator _end(_beg);

            k = *_beg; // start of change
			if (!_cmp(k, key) && !_cmp(key, k)) // check for // assigment // end of change
				++_end;
			return ft::make_pair(_beg, _end);
		}

	private:
		allocator_type	_mem;
		key_compare		_cmp;
        rb_tree         _rb_tree;

};

template< class Key, class Compare, class Alloc >
void swap(ft::set<Key, Compare,Alloc>& lhs, ft::set<Key, Compare,Alloc>& rhs)
{
	lhs.swap(rhs);
}

template< class Key,  class Compare, class Alloc >
bool operator==(const ft::set<Key, Compare,Alloc>& lhs, const ft::set<Key, Compare,Alloc>& rhs)
{

	if (lhs.size() == rhs.size())
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	return false;
}

template< class Key,  class Compare, class Alloc >
bool operator!=( const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class Key,  class Compare, class Alloc >
bool operator<(const ft::set<Key, Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), Compare());
}

template< class Key,  class Compare, class Alloc >
bool operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key, Compare,Alloc>& rhs)
{
	return rhs < lhs;
}

template< class Key,  class Compare, class Alloc >
bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template< class Key,  class Compare, class Alloc >
bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
{
	return !(lhs < rhs);
}

};


#endif
