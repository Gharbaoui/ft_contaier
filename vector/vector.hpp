#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream> // remove later

#include <memory>
#include <stdexcept>
namespace ft{
#include "is-integral.hpp"

template <
	typename T,
	typename Allocator = std::allocator<T>
>
class	vector{
	public:
		typedef T					value_type;
		typedef	size_t				size_type;
		typedef Allocator			allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef	ptrdiff_t			difference_type;

	/// member functions
		vector(){
			_size = 0;
			_index = 0;
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
			_index = count;
			_arr = mem_manager.allocate(_capacity);
			range_construct_def(0, _size);
		}
		vector(vector const &cp)
		{
			*this = cp;
		}
		explicit vector(const Allocator& alloc) : mem_manager(alloc)
		{
			_size = 0;
			_index = 0;
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
			_index = count;
			_capacity = count;
			_arr = mem_manager.allocate(_capacity);
			range_construct_value(0, _index, value);
		}
		template <typename InputIt>
		vector(InputIt first, InputIt last,
       	const Allocator& alloc = Allocator(),
		typename ft_enable<!is_integral<InputIt>::value>::type=true
		)
		{
			_max_size = mem_manager.max_size();
			_capacity = last - first;
			if (_capacity > _max_size)
				throw std::length_error("invalid length");
			_size = _capacity;
			_index = _size;
			_arr = mem_manager.allocate(_capacity);
			for (int i = 0; first != last; ++first) {
				mem_manager.construct(_arr + i, *first);
				++i;
			}
		}
		~vector(){
			range_destroy(0, _size, _capacity);
			_arr = NULL;
		}
		vector			&operator=(vector const &rhs)
		{
			if (this != &rhs) {
				if (_size)
					range_destroy(0, _size,  _capacity);
				_size = rhs._size;
				_index = rhs._index;
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
			if (count > _max_size)
				throw std::length_error("invalid length");
			_index = count;
			_size = count;
			if (count > _capacity){
				_capacity = count;
				_size = count;
				_index = count;
				range_destroy(0, _size, _capacity);
				_arr = mem_manager.allocate(_capacity);
			}
			for (int i = 0; i < _size; ++i)
				_arr[i] = value;
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
			return _arr[_index - 1];
		}
		const_reference back() const
		{
			return _arr[_index - 1];
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
			return (_index) ? false : true;
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
			_index = 0;
		}
		void			push_back(const T& val)
		{
			T *new_arr;
			size_t	old_cap;

			if (_index < _capacity)
				_arr[_index] = val;
			else {
				old_cap = _capacity;
			   _capacity *= 2;
				new_arr = mem_manager.allocate(_capacity);
				int i;
				for (i = 0; i < _size; ++i)
					mem_manager.construct(new_arr + i, _arr[i]);
				mem_manager.construct(new_arr + i, val);
				range_destroy(0, _size, old_cap);
				_arr = new_arr;
			}
			++_index;
			_size = _index;
		}
		void			pop_back()
		{
			if (_index){
				--_index;
				_size = _index;
				mem_manager.destroy(_arr + _index);
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
					for (int i = _index - 1; n > 0; --i) {
						mem_manager.destroy(_arr + i);
						--n;
					}
				}else {
					for (int i = _index; i < count + 1; ++i)
						mem_manager.construct(_arr + i, value);
				}
			}else{
				cur_cap = _capacity;
				if (count < 2 * _capacity)
					_capacity *= 2;
				else
					_capacity = count;
				new_arr = mem_manager.allocate(_capacity);
				for (int i = _index; i < count; ++i)
					mem_manager.construct(_arr + i, value);
				range_destroy(0, _size, cur_cap);
				_arr = new_arr;
			}
			_size = count;
			_index = _size;
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
					for (int i = _index - 1; n > 0; --i) {
						mem_manager.destroy(_arr + i);
						--n;
					}
				}else {
					for (int i = _index; i < count + 1; ++i)
						mem_manager.construct(_arr + i);
				}
			}else{
				cur_cap = _capacity;
				if (count < 2 * _capacity)
					_capacity *= 2;
				else
					_capacity = count;
				new_arr = mem_manager.allocate(_capacity);
				for (int i = _index; i < count; ++i)
					mem_manager.construct(_arr + i);
				range_destroy(0, _size, cur_cap);
				_arr = new_arr;
			}
			_size = count;
			_index = _size;
		}
		void 			swap(vector& other)
		{
			if (this == &other)
				return ;
			my_swap(_size, other._size);
			my_swap(_index, other._index);
			my_swap(_capacity, other._capacity);
			my_swap(_max_size, other._max_size);
			my_swap(mem_manager, other.mem_manager);
			my_swap(_arr, other._arr);
		}
	private:
		T					*_arr;
		size_t				_size;
		size_t				_index;
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
		}
};

template <typename T>
void	my_swap(T &a, T &b)
{
	T c = a;
	a = b;
	b = c;
}

}
#endif
