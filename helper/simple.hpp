#ifndef	SIMPLE_HPP
#define	SIMPLE_HPP

namespace ft{

	template <bool, typename=bool>
	struct enable_if{};

	template <typename T>
	struct enable_if<true, T> {typedef	T type;};

	template <typename RandIter>
	typename	RandIter::difference_type	distance(RandIter beg, RandIter end, ft::random_access_iterator_tag)
	{
		return end - beg;
	}
	template <typename InputIter>
	typename InputIter::difference_type	distance(InputIter beg, InputIter end, ft::input_iterator_tag)
	{
		typedef	typename InputIter::difference_type retType;
		retType counter = retType();
		while (beg != end)
		{
			++beg;
			++counter;
		}
		return counter;
	}
	template <typename Iter>
	typename Iter::difference_type	distance(Iter beg, Iter end)
	{
		typename Iter::iterator_category category;
		return ft::distance(end, beg, category);
	}
	
};

#endif
