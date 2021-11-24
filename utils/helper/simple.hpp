#ifndef	SIMPLE_HPP
#define	SIMPLE_HPP

namespace ft{

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


	template <bool, typename=bool>
	struct enable_if{};

	template <typename T>
	struct enable_if<true, T> {typedef	T type;};

	template <typename T>
	struct is_po_to_const{
		static const bool value = false;
	};

	template <typename T>
	struct is_po_to_const<T  const *>
	{
		static const bool value = true;
	};

	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (pred(*first1 ,*first2))
				return false;
			++first1;
			++first2;
		}
		return true;
		
	}

};

#endif
