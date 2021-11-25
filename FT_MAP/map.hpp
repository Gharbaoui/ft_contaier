#ifndef MAP_HPP
#define MAP_HPP

#include  <stdexcept>
#include <unistd.h>
#include  <utility>
#include "../utils/helper/pair.hpp"
#include "../utils/helper/simple.hpp"
#include "../utils/RB_TREE/red-black.hpp"
#include "../utils/iterator-traits/iterator-traits.hpp"
#include "../utils/iterator-traits/iterators.hpp"
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
		typedef	Key																				key_type;
		typedef	T																				mapped_type;
		typedef	ft::pair<const Key, T>															value_type;
		typedef	ft::pair<const Key, const T>													const_value_type;
		typedef	size_t																			size_type;
		typedef	std::ptrdiff_t																	difference_type;
		typedef	Compare																			key_compare;
		typedef	Allocator																		allocator_type;
		typedef	value_type&																		reference;
		typedef	const value_type&																const_reference;
        typedef RB_manager<value_type, key_compare, key_type, allocator_type>					rb_tree;
        typedef rb_iterator<value_type, value_type&, value_type*, allocator_type>				iterator;
        typedef rb_iterator<value_type, value_type const&, value_type const*, allocator_type>	const_iterator;
		typedef	ft::reverse_iterator<iterator>													reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>									        const_reverse_iterator;
		typedef	RB_node<value_type>																node;


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
		map() : def(), _rb_tree() {}
        ~map () {clear();}
		explicit map(const Compare& comp, const Allocator& alloc = Allocator())
        : def(), _mem(alloc), _cmp(comp), _rb_tree() {}

		template< class InputIt >
		map(InputIt first, InputIt last,
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
		
		map(const map &cp)
		{
			insert(cp.begin(), cp.end());
		}

		map& operator=(const map& other)
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
		mapped_type& operator[] (const key_type& k)
		{
			node *n = _rb_tree.find(k);
			if (n)
				return n->item.second;
			else
				return _rb_tree.insert_with_no_find(ft::make_pair(k, def)).second;
		}
		T& at( const Key& key )
		{
			node *n = _rb_tree.find(key);
			if (n)
				return n->item.second;
			throw std::out_of_range("there's no element with this key");
		}

		const T& at( const Key& key ) const
		{
			node *n = _rb_tree.find(key);
			if (n)
				return n->item.second;
			throw std::out_of_range("there's no element with this key");
		}
		
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

		void swap( map& other )
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
			iterator _beg(begin());
			iterator _end(end());

			while (_beg != _end)
			{
				if (!_cmp(_beg->first, key))
					break ;
				++_beg;
			}
			return _beg;
		}

		const_iterator lower_bound( const Key& key ) const
		{
			const_iterator _beg(begin());
			const_iterator _end(end());

			while (_beg != _end)
			{
				if (!_cmp(_beg->first, key))
					break ;
				++_beg;
			}
			return _beg;
		}

		iterator upper_bound( const Key& key )
		{
			// return iterator to first greater elm after key
			//so this to be true iter->first should be greater than key
			iterator _beg(begin());
			iterator _end(end());
			while (_beg != _end)
			{
				if (_cmp(key, _beg->first))
					break ;
				++_beg;
			}
			return _beg;
		}

		const_iterator upper_bound( const Key& key ) const
		{
			// return iterator to first greater elm after key
			//so this to be true iter->first should be greater than key
			const_iterator _beg(begin());
			const_iterator _end(end());
			while (_beg != _end)
			{
				if (_cmp(key, _beg->first))
					break ;
				++_beg;
			}
			return _beg;
		}
		
		key_compare key_comp() const
		{
			return _cmp;
		}

		value_compare value_comp() const
		{
			return value_compare(_cmp);
		}
		
		ft::pair<iterator,iterator> equal_range(const Key& key)
		{
			iterator _beg(begin());
			iterator _end(end());

			while (_beg != _end)
			{
				if (!_cmp(_beg->first, key))
					break ;
				++_beg;
			}
			_end = _beg;
			if (_beg->first == key)
				++_end;
			return ft::make_pair(_beg, _end);
		}

		ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const
		{
			const_iterator _beg(begin());
			const_iterator _end(end());

			while (_beg != _end)
			{
				if (!_cmp(_beg->first, key))
					break ;
				++_beg;
			}
			_end = _beg;
			if (_beg->first == key)
				++_end;
			return ft::make_pair(_beg, _end);
		}

	private:
		mapped_type		def;
		allocator_type	_mem;
		key_compare		_cmp;
        rb_tree         _rb_tree;

};
template< class Key, class T, class Compare, class Alloc >
void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
{
	lhs.swap(rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{

	if (lhs.size() == rhs.size())
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	return false;
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return rhs < lhs;
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return !(rhs < lhs);
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return !(lhs < rhs);
}

};


#endif
