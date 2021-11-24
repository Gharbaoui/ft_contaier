#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS
#include <type_traits>
#include <iterator>
namespace ft
{
	template <typename Iter>
	struct iterator_traits{
		typedef	typename	Iter::value_type		value_type;
		typedef	typename	Iter::iterator_category	iterator_category;
		typedef	typename	Iter::difference_type	difference_type;
		typedef	typename	Iter::pointer			pointer;
		typedef	typename	Iter::reference			reference;
	};

	template <typename PT>
	struct	iterator_traits<PT*>
	{
		typedef	typename std::remove_cv<PT>::type			value_type;
		typedef	typename std::random_access_iterator_tag	iterator_category;
		typedef	ptrdiff_t									difference_type;
		typedef	PT*											pointer;
		typedef	PT&											reference;
	};

	template <typename Iter>
	struct has_type{
		// the trick is not here the trick is on what is calling this if the type is trying to test does not has type it will fail there (good)
		static const bool value = true;
	};
	template <typename T, typename U>
	struct is_same{
		static const bool value = std::is_same<std::remove_const<T>, std::remove_const<U> >::value;
	};
	
	template <typename  Iter, typename Iter_Type>
	struct can_inter_change{
		// primary use is to make iterator to const_iterator possible
		// it takes two iterators and check if they point to the same type
		// and i iterator_traits bec if i did just Iter_Type::value_type if Iter_Type was int * i got error
		// in that case ther specialization in iterator_traits for pointers 
		static const bool value = std::is_same<
			typename ft::iterator_traits<Iter>::value_type,
			typename ft::iterator_traits<Iter_Type>::value_type
		>::value;
	};

    template <typename T>
    struct p_to_const{
        static const  bool value = false;
    };

    template <typename T>
    struct p_to_const<const T *>
    {
        static const bool value = true;
    };
    
};

#endif
