#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream> // remove later

#include <memory>
#include <stdexcept>
#include "../helper/simple.hpp"
#include "../helper/is-integral.hpp"
#include "../iterator-traits/iterator-traits.hpp"
#include "../iterator-traits/iterators.hpp"

namespace ft{

template <typename T>
void	my_swap(T &a, T &b)
{
	T c = a;
	a = b;
	b = c;
}

template <
	typename T,
	typename Allocator = std::allocator<T>
>
class	vector{
	public:
		typedef T														value_type;
		typedef	size_t													size_type;
		typedef Allocator												allocator_type;
		typedef value_type&												reference;
		typedef const value_type&										const_reference;
		typedef	ptrdiff_t												difference_type;
		typedef	random_access_iterator<T*>								iterator;
		typedef	random_access_iterator<const T*>						const_iterator;
		typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
	/// member functions
		vector(){
			_size = 0;
			_capacity = 0;
			_arr = NULL;
			_max_size = mem_manager.max_size();
		}
		explicit vector(size_type count){
			_max_size = mem_manager.max_size();
			if (count > _max_size)
				throw std::length_error("invalid length");
			_size = count;
			_capacity = count;
			_arr = mem_manager.allocate(_capacity);
			range_construct_def(0, _size);
		}
		vector(vector const &cp)
		{
			_size = 0; // when = will used here inside =op will we size to detrmin weather to free or not
			*this = cp;
		}
		explicit vector(const Allocator& alloc) : mem_manager(alloc)
		{
			_size = 0;
			_capacity = 0;
			_arr = NULL;
			_max_size = mem_manager.max_size();	
		}
		explicit 		vector( size_type count,
		const T& value,
		const Allocator& alloc = Allocator()) : mem_manager(alloc)
		{
			_max_size = mem_manager.max_size();
			if (count > _max_size)
				throw std::length_error("invalid length");
			_size = count;
			_capacity = count;
			_arr = mem_manager.allocate(_capacity);
			range_construct_value(0, _size, value);
		}
		template <typename InputIt>
		vector(InputIt first, InputIt last,
       	const Allocator& alloc = Allocator(),
		typename ft::enable_if<!ft::is_integral<InputIt>::value>::type=true
		)
		{
			_max_size = mem_manager.max_size();
			_capacity = last - first;
			if (_capacity > _max_size)
				throw std::length_error("invalid length");
			_size = _capacity;
			_arr = mem_manager.allocate(_capacity);
			for (int i = 0; first != last; ++first) {
				mem_manager.construct(_arr + i, *first);
				++i;
			}
		}
		~vector(){
			range_destroy(0, _size, _capacity);
			_size = 0;
			_capacity = 0;
			_arr = NULL;
		}
		vector			&operator=(vector const &rhs)
		{
			if (this != &rhs) {
				if (_size)
					range_destroy(0, _size,  _capacity);
				_size = rhs._size;
				_capacity = rhs._capacity;
				mem_manager = rhs.mem_manager;
				_arr = mem_manager.allocate(_capacity);
				for (int i = 0; i < _size; ++i)
					mem_manager.construct(_arr + i, rhs._arr[i]);
			}
			return *this;
		}
		void			assign(size_type count, const T& value)
		{
			bool not_constructed = false; // i assume that already constructed
			if (count > _max_size)
				throw std::length_error("invalid length");
			if (count > _capacity){
				not_constructed = true;
				range_destroy(0, _size, _capacity);
				_capacity = count;
				_arr = mem_manager.allocate(_capacity);
			}
			_size = count;
			for (int i = 0; i < _size; ++i){
				if (not_constructed)
					mem_manager.construct(_arr + i, value);
				else
					_arr[i] = value;
			}
		}
		template <typename Iter>
		void	assign(Iter first, Iter last, typename ft::enable_if<!ft::is_integral<Iter>::value>::type=true)
		{
			bool not_constructed = false; // i assume that already constructed
			size_type count;
			count = last - first;
			if (count > _max_size)
				throw std::length_error("invalid length");
			if (count > _capacity){
				not_constructed = true;
				range_destroy(0, _size, _capacity);
				_capacity = count;
				_arr = mem_manager.allocate(_capacity);
			}
			_size = count;
			int i = 0;
			for (; first != last; ++first) {
				if (not_constructed)
					mem_manager.construct(_arr + i, *first);
				else
					_arr[i] = *first;
				++i;
			}
		}
		allocator_type	get_allocator() const{
			return mem_manager;
		}

		// element access
		reference		operator[](size_t i){
			return _arr[i];
		}
		const_reference	operator[](size_t i) const{
			return _arr[i];
		}
		reference		at(size_type pos){
			if (pos >= _size)
				throw std::out_of_range("out of range");
			return _arr[pos];
		}
		const_reference at(size_type pos) const{
			if (pos >= _size)
				throw std::out_of_range("out of range");
			return _arr[pos];
		}
		reference		front(){
			return _arr[0];
		}
		const_reference front() const{
			return _arr[0];
		}
		reference		back(){
			return _arr[_size - 1];
		}
		const_reference back() const
		{
			return _arr[_size - 1];
		}
		T				*data(){
			if (_size == 0)
				return NULL;
			return _arr;
		}
		T	const		*data() const{
			if (_size == 0)
				return NULL;
			return _arr;
		}

		// capacity
		bool empty() const{
			return (_size) ? false : true;
		}
		size_type		max_size() const{
			return _max_size;
		}
		size_t			size() const{
			return _size;
		}
		size_type		capacity() const{
			return _capacity;
		}
		void			reserve(size_type new_cap)
		{
			T	*new_arr;
			if (new_cap > _max_size)
				throw std::length_error("invalid length");
			if (_capacity < new_cap){
				new_arr = mem_manager.allocate(new_cap);
				for (int i = 0; i < _size; ++i)
					mem_manager.construct(new_arr + i , _arr[i]);
		//		for (int i = _size; i < new_cap; ++i)
		//			mem_manager.construct(new_arr + i);
				range_destroy(0, _size, _capacity);
				_arr = new_arr;
				_capacity = new_cap;
			}
		}
		void			shrink_to_fit()
		{
			T	*new_arr;
			if (_capacity > _size)
			{
				new_arr = mem_manager.allocate(_size);
				for (int i = 0; i < _size; ++i)
					mem_manager.construct(new_arr + i,  _arr[i]);
				range_destroy(0, _size, _capacity);
				_capacity = _size;
				_arr = new_arr;
			}
		}

		//modifiers
		void			clear()
		{
			for (int i = 0; i < _size;  ++i)
				mem_manager.destroy(_arr + i);
			_size = 0;
		}
		iterator insert(iterator where, const T& value)
		{
			size_type pos = &(*where) - _arr;
			make_gap_in(1, pos);
			if (pos > _size)
				_size = pos;
			mem_manager.construct(_arr + pos, value);
			++_size;
			return _arr + pos;
		}


		void insert(iterator where, size_type count, const T& value)
		{
			int count_save = count;
			size_type pos = &(*where) - _arr;
			make_gap_in(count, pos);
			for (int i = pos; count--; ++i)
			{
				mem_manager.construct(_arr + i, value);
			}
			if (pos >= _size)
				_size = pos;
			_size += count_save;
		}

		template<class InputIt>
		void insert(iterator where, InputIt first, InputIt last,
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type=false)
		{
			size_type pos = &(*where) - _arr;
			int count = last - first;
			make_gap_in(count, pos);
			int i = pos;
			while (first != last)
			{
				mem_manager.construct(_arr + i, *first);
				++first;
				++i;
			}
			if (pos >= _size)
				_size = pos;
			_size += count;
		}

		iterator erase(iterator where) {
			size_type pos = &(*where) - _arr;
			if (pos < _size) {
				for (int i = pos; i < _size - 1; ++i)
					_arr[i] = _arr[i + 1];
				--_size;
			}
			if (pos >= _size - 1)
				return end();
			return iterator(_arr + pos);
		}
		iterator erase(iterator first, iterator last)
		{
			size_type count =  last - first;
			size_type pos = &(*first) - _arr;
			if (pos <= _size)
			{
				pos = &(*last) - _arr;
				if (pos <= _size) {
					for (int i = pos; i < _size; ++i)
						_arr[i - count] = _arr[i];
					_size -= count;
				}
			}
			if (&(*last) == _arr + (_size + count))
				return end();
			return first;

		}
		void			push_back(const T& val)
		{
			T *new_arr;
			size_t	old_cap;

			if (_size < _capacity)
				mem_manager.construct(_arr + _size, val);
			else {
				old_cap = _capacity;
				if (!_capacity)
					_capacity = 1;
				else
			   		_capacity *= 2;
				new_arr = mem_manager.allocate(_capacity);
				int i;
				for (i = 0; i < _size; ++i)
					mem_manager.construct(new_arr + i, _arr[i]);
				mem_manager.construct(new_arr + i, val);
				range_destroy(0, _size, old_cap);
				_arr = new_arr;
			}
			++_size;
		}
		void			pop_back()
		{
			if (_size){
				--_size;
				mem_manager.destroy(_arr + _size);
			}
		}
		void			resize(size_type count, const T &value)
		{
			int	n;
			T	*new_arr;
			size_type cur_cap;

			if (count > _max_size)
				throw std::length_error("invalid length");
			if (count < _capacity) {
				if (count < _size) {
					n = _size - count;
					for (int i = _size - 1; n > 0; --i) {
						mem_manager.destroy(_arr + i);
						--n;
					}
				}else {
					for (int i = _size; i < count + 1; ++i)
						mem_manager.construct(_arr + i, value);
				}
			}else{
				cur_cap = _capacity;
				if (count < 2 * _capacity)
					_capacity *= 2;
				else
					_capacity = count;
				new_arr = mem_manager.allocate(_capacity);
				for (int i = 0; i < _size; ++i)
					mem_manager.construct(new_arr + i, _arr[i]);
				for (int i = _size; i < _capacity; ++i)
					mem_manager.construct(new_arr + i, value);
				range_destroy(0, _size, cur_cap);
				_arr = new_arr;
			}
			_size = count;
		}
		void			resize(size_type count)
		{
			int	n;
			T	*new_arr;
			size_type cur_cap;

			if (count > _max_size)
				throw std::length_error("invalid length");
			if (count < _capacity) {
				if (count < _size) {
					n = _size - count;
					for (int i = _size - 1; n > 0; --i) {
						mem_manager.destroy(_arr + i);
						--n;
					}
				}else {
					for (int i = _size; i < count + 1; ++i)
						mem_manager.construct(_arr + i);
				}
			}else{
				cur_cap = _capacity;
				if (count < 2 * _capacity)
					_capacity *= 2;
				else
					_capacity = count;
				new_arr = mem_manager.allocate(_capacity);
				for (int i = 0; i < _size; ++i)
					mem_manager.construct(new_arr + i, _arr[i]);
				for (int i = _size; i < _capacity; ++i)
					mem_manager.construct(new_arr + i);
				range_destroy(0, _size, cur_cap);
				_arr = new_arr;
			}
			_size = count;
		}
		void 			swap(vector& other)
		{
			if (this == &other)
				return ;
			my_swap(_size, other._size);
			my_swap(_capacity, other._capacity);
			my_swap(_max_size, other._max_size);
			my_swap(mem_manager, other.mem_manager);
			my_swap(_arr, other._arr);
		}

		////
		iterator	begin() {
			return iterator(_arr);
		};
		iterator	end() {
			return iterator(_arr + _size);
		}

		const_iterator	begin() const {
			return const_iterator(_arr);
		}
		const_iterator	end() const
		{
			return const_iterator(_arr + _size);
		}

		reverse_iterator	rbegin()
		{
			return	reverse_iterator(_arr + _size);
		}
		
		reverse_iterator	rend()
		{
			return	reverse_iterator(_arr);
		}

		const_reverse_iterator	rbegin() const
		{
			return	const_reverse_iterator(_arr + _size);
		}
		
		const_reverse_iterator	rend() const
		{
			return	const_reverse_iterator(_arr);
		}

	private:
		T					*_arr;
		size_t				_size;
		size_t				_capacity;
		size_t				_max_size;
		allocator_type		mem_manager;
	private:
		void			range_construct_def(int start, int end)
		{
			for (; start < end;  ++start)
				mem_manager.construct(_arr + start);
		}
		void		range_construct_value(int start, int end, const T& value)
		{
			for (; start < end;  ++start)
				mem_manager.construct(_arr + start, value);
		}
		void			range_destroy(int start, int end, int cap)
		{
			for (int i = start; i < end; ++i)
				mem_manager.destroy(_arr + i);
			mem_manager.deallocate(_arr , cap);
			_arr = NULL;
		}
		void			make_gap_in(size_type gap_size, size_type start_of_gap) // help make gap in _arr with size provided
		{
			bool already_in_place = false;
			if (!(_size + gap_size <= _capacity))
			{
				already_in_place = true;
				size_type cur_cap = _capacity;
				T *_new_arr;
				if (_capacity * 2 < gap_size)
					_capacity += gap_size;
				else
					_capacity *= 2;
				_new_arr = mem_manager.allocate(_capacity);
				for (int i = 0; (i < _size && i < start_of_gap); ++i)
					mem_manager.construct(_new_arr + i, _arr[i]);
				if (start_of_gap < _size)
					for (int i = _size - 1; i >= start_of_gap; --i)
						mem_manager.construct(_new_arr + (i + gap_size) , _arr[i]);
				range_destroy(0, _size, cur_cap);
				_arr = _new_arr;
			}
			if (!already_in_place) {
				if (start_of_gap < _size)
					for (int i = _size - 1; i >= start_of_gap; --i)
						mem_manager.construct(_arr + (i + gap_size), _arr[i]);
			}
		}
};

template< class T, class Alloc > 
bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
{
	int size = lhs.size();
	if (size != rhs.size())
		return false;
	for (int i = 0; i < size; ++i) {
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) 
{
	return !(rhs == lhs);
}

template <typename Iter1, typename Iter2>
bool	lexicographical_compare(Iter1 f1, Iter1 l1, Iter2 f2, Iter2 l2) // if elment in range 1 is less than elment in range 2 (true) if range1 is done before range 2 (true) if not false
{
	while (f1 != l1)
	{
		if (f2 == l2) // second has done
			return false;
		else if (*f1 < *f2)
			return true;
		else if (*f2 < *f1)  // doing 2 comap bec == does not count to one of them
			return false;
		++f1;
		++f2;
	}
	if (f2 == l2) // if second range done and we are reached here return false
		return false;
	return true;
}

template< class T, class Alloc >
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); 
}

template< class T, class Alloc >
bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}


// true if lhs is less than or equal to right hand side
//  4<=5  true 4<=4 true but 5 <= 4 is false
//
template< class T, class Alloc >
bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	// can you less than operator a <= b can be expressed in terms of < 
	// a<=b means that b would never be small than a so => !(b < a)
	return !(rhs < lhs);
}

template< class T, class Alloc >
bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	// can you less than operator a >= b can be expressed in terms of < 
	// a >= b means that a would never be small than b so => !(a < b)
	return !(lhs < rhs);
}

template< class T, class Alloc >
void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
{
	lhs.swap(rhs);
}




};
#endif
