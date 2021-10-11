#ifndef MODIFIERS
#define MODIFIERS

template <typename T, typename Alloc>
void	vector<T, Alloc>::clear()
{
	_clear_worked = true;
	//range_destroy(0, _size, _capacity);
	_usr_cap = _capacity;
	_capacity = 0;
	_size = 0;
	_index = 0;
}

template <typename T, typename Alloc>
void	vector<T, Alloc>::push_back(T const &val)
{
	T *new_arr;
	size_t	cur_cap;

	if (_index < _capacity)
	{
		_arr[_index] = val;
	}else{
		cur_cap = (_clear_worked) ? _usr_cap : _capacity;
	   _capacity = cur_cap * 2;
   		new_arr = mem_manager.allocate(_capacity);
		int i;
		for (i = 0; i < _size; ++i)
			new_arr[i] = _arr[i];
		new_arr[i] = val;
		range_destroy(0, _size, cur_cap);
		_arr = new_arr;
	}
	++_index;
	_size = _index;
	_clear_worked = false;
}

template <typename T, typename Alloc>
void	vector<T, Alloc>::pop_back()
{
	if (_index){
		--_index;
		_size = _index;
		mem_manager.destroy(_arr + _index);
	}
}

template <typename T, typename Alloc>
void	vector<T, Alloc>::resize(size_type count, T value)
{
	/// stops herre
}

#endif
