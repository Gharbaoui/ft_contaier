#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template <typename T1, typename T2>
struct pair
{
	typedef	T1	first_type;
	typedef	T2	second_type;
	pair() : first(first_type()), second(second_type()){}
	pair(const T1& x, const T2& y) : first(x), second(y) {}
	template< class U1, class U2 >
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
	~pair(){}
	pair	&operator=(const pair& rhs){
		if (this != &rhs)
		{
			first = rhs.first;
			second = rhs.second;
		}
		return *this;
	}
	// objs
	first_type	first;
	second_type	second;

};

template<class T1, class T2>
ft::pair<T1,T2> make_pair(T1 t, T2 u)
{
	return ft::pair<T1, T2>(t, u);
}

template< class T1, class T2 >
bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
	if (lhs.first == rhs.first && lhs.second == rhs.second)
		return true;
	return false;
}

template< class T1, class T2 >
bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
	return !(lhs == rhs);
}

template< class T1, class T2 >
bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
	if (lhs.first< rhs.first)
		return true;
	if (rhs.first < lhs.first)
		return false;

	if (lhs.second < rhs.second)
		return true;
	return false;
}

template< class T1, class T2 >
bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
	return !(rhs < lhs);
}

template< class T1, class T2 >
bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
	return  (rhs < lhs);
}

template< class T1, class T2 >
bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
{
	return  !(lhs < rhs);
}

template<
    class Arg1,
    class Arg2,
    class Result
> struct binary_function
{
	typedef	Arg1	first_argument_type;
	typedef	Arg2	second_argument_type;
	typedef	Result	result_type;
};

}
#endif
