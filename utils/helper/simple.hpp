#ifndef	SIMPLE_HPP
#define	SIMPLE_HPP

namespace ft{

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
};

#endif
