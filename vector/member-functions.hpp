#ifndef MEMBER_FUNCTIONS
#define MEMBER_FUNCTIONS

template <typename T, typename Allocator>
vector<T, Allocator>::vector()
{
	_clear_worked = false;
	_size = 0;
	_index = 0;
	_capacity = 0;
	_arr = NULL;
	_max_size = mem_manager.max_size();
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(Alloc const &alloc) : mem_manager(alloc)
{
	_clear_worked = false;
	_size = 0;
	_index = 0;
	_capacity = 0;
	_arr = NULL;
	_max_size = mem_manager.max_size();
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type count)
{
	_max_size = mem_manager.max_size();
	if (count > _max_size)
		throw std::length_error("invalid length");
	_clear_worked = false;
	_size = count;
	_capacity = count;
	_index = count;
	_arr = mem_manager.allocate(_capacity);

	for (int i = 0; i < _size; ++i)
		mem_manager.construct(_arr + i);
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector const &cp)
{
//	_size = 0; if error look here
	*this = cp;
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type count,
	const T& value,
	const Allocator& alloc
) : mem_manager(alloc)
{
	_max_size = mem_manager.max_size();
	if (count > _max_size)
		throw std::length_error("invalid length");
	_clear_worked = false;
	_size = count;
	_index = count;
	_capacity = count;
	_arr = mem_manager.allocate(_capacity);
	for (int i = _index - 1; i >= 0; --i)
		mem_manager.construct(_arr + i, value);
}

template <typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
	_size = 0;
	_index = 0;
	_capacity = 0;
	_clear_worked = false;
	range_destroy(0, _size, _capacity);
	_arr = NULL;
}

template <typename T, typename Allocator>
vector<T, Allocator>
&vector<T, Allocator>::operator=(vector const &rhs)
{
	if (this != &rhs) {
		if (_size)
			range_destroy(0, _size,  _capacity);
		_size = rhs._size;
		_index = rhs._index;
		_clear_worked = rhs._clear_worked;
		_capacity = rhs._capacity;
		_clear_worked = false;
		mem_manager = rhs.mem_manager;
		_arr = mem_manager.allocate(_capacity);
		for (int i = 0; i < _size; ++i)
			mem_manager.construct(_arr + i, rhs._arr[i]);
	}
	return *this;
}

template <typename T, typename Alloc>
void	vector<T, Alloc>::assign(size_type count, const T& value)
{
	if (count > _max_size)
		throw std::length_error("invalid length");
	if (count < _capacity)
	{
		_index = count;
		_size = count;
		for (int i = 0; i < _size; ++i)
			_arr[i] = value;
	}else{
		_capacity = count;
		_clear_worked = false;
		_size = count;
		_index = count;
		range_destroy(0, _size, _capacity);
		_arr = mem_manager.allocate(_capacity);
		for (int i = 0; i < _size; ++i)
			_arr[i] = value;
	}
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type
vector<T, Alloc>::get_allocator() const
{
	return mem_manager;
}

#endif
