#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS

namespace ft
{
	struct	input_iterator_tag{};
	struct	output_iterator_tag{};
	struct	forward_iterator_tag : input_iterator_tag {};
	struct	bidirectional_iterator_tag : forward_iterator_tag{};
	struct	random_access_iterator_tag : bidirectional_iterator_tag{};

	template <typename Iter>
	struct iterator_traits{
		typedef	typename	Iter::value_type		value_type;
		typedef	typename	Iter::iterator_category	iterator_category;
		typedef	typename	Iter::difference_type	difference_type;
		typedef	typename	Iter::pointer			pointer;
		typedef	typename	Iter::refernce			reference;
	};
};

#endif
