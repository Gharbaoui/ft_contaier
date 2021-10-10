#ifndef ELEMENT_ACCESS
#define	ELEMENT_ACCESS

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::at(size_type pos)
{
	if (pos >= _size)
		throw std::out_of_range("out of range");
	return _arr[pos];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::at(size_type pos) const
{
	if (pos >= _size)
		throw std::out_of_range("out of range");
	return _arr[pos];
}

template <typename T, typename Alloc>
T	&vector<T, Alloc>::operator[] (size_t i)
{
	return _arr[i];
}


template <typename T, typename Alloc>
T const 	&vector<T, Alloc>::operator[] (size_t i) const
{
	return _arr[i];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::front()
{
	return _arr[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::front() const
{
	return _arr[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::back()
{
	return _arr[_index - 1];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::back() const
{
	return _arr[_index - 1];
}

template <typename T, typename Alloc>
T	*vector<T, Alloc>::data()
{
	if (_size == 0)
		return NULL;
	return _arr;
}

template <typename T, typename Alloc>
T	const *vector<T, Alloc>::data () const
{
	if (_size == 0)
		return NULL;
	return _arr;
}

#endif
