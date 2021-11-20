#ifndef	SIMPLE_HPP
#define	SIMPLE_HPP

namespace ft{

	template <bool, typename=bool>
	struct enable_if{};

	template <typename T>
	struct enable_if<true, T> {typedef	T type;};
};

#endif
