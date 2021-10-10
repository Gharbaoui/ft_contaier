#ifndef	CAPACITY
#define	CAPACITY


template <typename T, typename Alloc>
bool	vector<T, Alloc>::empty() const
{
	return (_index) ? false : true;
}

template <typename T, typename Alloc>
size_t	vector<T, Alloc>::size() const
{
	return _size;
}
template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T,Alloc>::max_size()  const
{
	return _max_size;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::capacity() const
{
	if (_clear_worked)
		return _usr_cap;
	return _capacity;
}

template <typename  T, typename Alloc>
void	vector<T, Alloc>::reserve(size_type new_cap)
{
	T	*new_arr;
	if (new_cap > _max_size)
		throw std::length_error("invalid length");
	if (_capacity < new_cap){
		new_arr = mem_manager.allocate(new_cap);
		for (int i = 0; i < _size; ++i)
			new_arr[i] = _arr[i];
		range_destroy(0, _size, _capacity);
		_arr = new_arr;
		_capacity = new_cap;
	}
}

template <typename T, typename Alloc>
void	vector<T, Alloc>::shrink_to_fit()
{
	T	*new_arr;
	if (_capacity > _size)
	{
		new_arr = mem_manager.allocate(_size);
		for (int i = 0; i < _size; ++i)
			new_arr[i] = _arr[i];
		range_destroy(0, _size, _capacity);
		_capacity = _size;
		_arr = new_arr;
	}
}

#endif
