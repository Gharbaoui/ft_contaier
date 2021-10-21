#ifndef	ITERATOR_HPP
#define ITERATOR_HPP

namespace ft{
	template <typename T>
	struct remove_ptr{typedef T type;};
	template <typename T>
	struct remove_ptr<T*>{typedef T type;};
	template <typename T, typename U>
	struct	work_whene_both_are_iter {};
	template <typename T>
	struct 	work_whene_both_are_iter<T, T> {
		typedef	 T	type;
	};

	template <typename PT, typename D=ptrdiff_t>
	class random_access_iterator{
		public:
			typedef	ft::random_access_iterator_tag			iterator_category;
			typedef	typename ft::remove_ptr<PT>::type		value_type;
			typedef	D										difference_type;
			typedef	difference_type							my_diff_type;
			typedef	PT										pointer;
			typedef	value_type&								reference;
			typedef	bool									my_bool;
			random_access_iterator () : _cur_elem(NULL) {} // default constructor
			random_access_iterator (pointer p) : _cur_elem(p) {} // pointer constructor
			random_access_iterator(const random_access_iterator &cp) : _cur_elem (cp._cur_elem) {} // copy-constructor
			random_access_iterator	&operator=(const random_access_iterator &rhs){
				_cur_elem = rhs._cur_elem;
				return *this;
			}
			template <typename Iter>
			random_access_iterator (const Iter &cp) : _cur_elem(cp.base()) {} // used to construct const_iterator from iterator
			template <typename Iter>
			random_access_iterator	&operator=(const Iter &rhs) // used to assign from iterator to const_iterator
			{
				_cur_elem = rhs.base();
				return *this;
			}
			pointer	base() const{
				return _cur_elem;
			}
			// elment access
			reference	operator*() const {return *_cur_elem;}
			pointer		operator->() const {return _cur_elem;}
			reference	operator[](size_t index) const {return *(_cur_elem + index);}

			// arithmetic operations
			random_access_iterator	&operator+=(difference_type n){_cur_elem += n; return *this;}
			random_access_iterator	&operator-=(difference_type n){_cur_elem -= n; return *this;}
			random_access_iterator	operator+(difference_type n){return _cur_elem + n;}
			random_access_iterator	operator-(difference_type n){return _cur_elem - n;}
			random_access_iterator	&operator++(){++_cur_elem; return *this;}
			random_access_iterator	&operator--(){--_cur_elem; return *this;}
			random_access_iterator	&operator++(int){
				random_access_iterator tmp(_cur_elem);
				++_cur_elem;
				return *this;
			}
			random_access_iterator	&operator--(int){
				random_access_iterator tmp(_cur_elem);
				--_cur_elem;
				return tmp;
			}
		private:
			pointer	_cur_elem;
				
	};

	template <typename LIter, typename RIter>
	typename work_whene_both_are_iter<typename LIter::my_diff_type, typename RIter::my_diff_type>::type
	operator-(const LIter &_lhs, const RIter &_rhs)
	{
		return _lhs.base() - _rhs.base();
	}

	template <typename Iter>
	Iter	operator+(typename Iter::my_diff_type n, Iter i)
	{
		i += n;
		return i;
	}
	template <typename LIter, typename RIter>
	typename LIter::my_bool operator<(const LIter &a, const RIter &b)
	{
		return a.base() < b.base();
	}
	template <typename LIter, typename RIter>
	typename LIter::my_bool operator<=(const LIter &a, const RIter &b)
	{
		return a.base() <= b.base();
	}
	template <typename LIter, typename RIter>
	typename LIter::my_bool operator>(const LIter &a, const RIter &b)
	{
		return a.base() > b.base();
	}
	template <typename LIter, typename RIter>
	typename LIter::my_bool operator>=(const LIter &a, const RIter &b)
	{
		return a.base() >= b.base();
	}
	template <typename LIter, typename RIter>
	typename LIter::my_bool operator==(const LIter &a, const RIter &b)
	{
		return a.base() == b.base();
	}
	template <typename LIter, typename RIter>
	typename LIter::my_bool operator!=(const LIter &a, const RIter &b)
	{
		return a.base() != b.base();
	}
	// reverese starts here and uses some of above function template
	template <typename PT, typename D=ptrdiff_t>
	class rev_iterator{
		public:
			typedef	ft::random_access_iterator_tag			iterator_category;
			typedef	typename ft::remove_ptr<PT>::type		value_type;
			typedef	D										difference_type;
			typedef	difference_type							my_rev_diff_type;
			typedef	PT										pointer;
			typedef	value_type&								reference;
			typedef	bool									my_rev_bool;
			rev_iterator () : _cur_elem(NULL) {} // default constructor
			rev_iterator (pointer p) : _cur_elem(p) {} // pointer constructor
			rev_iterator(const rev_iterator &cp) : _cur_elem (cp._cur_elem) {} // copy-constructor
			rev_iterator	&operator=(const rev_iterator &rhs){
				_cur_elem = rhs._cur_elem;
				return *this;
			}
			template <typename Iter>
			rev_iterator (const Iter &cp) : _cur_elem(cp.base()) {} // used to construct const_iterator from iterator
			template <typename Iter>
			rev_iterator	&operator=(const Iter &rhs) // used to assign from iterator to const_iterator
			{
				_cur_elem = rhs.base();
				return *this;
			}
			pointer	base() const{
				return _cur_elem;
			}
			// elment access
			reference	operator*() const {return *_cur_elem;}
			pointer		operator->() const {return _cur_elem;}
			reference	operator[](size_t index) const {return *(_cur_elem - index);}

			// arithmetic operations
			rev_iterator	&operator+=(difference_type n){_cur_elem -= n; return *this;}
			rev_iterator	&operator-=(difference_type n){_cur_elem += n; return *this;}
			rev_iterator	operator+(difference_type n){return _cur_elem - n;}
			rev_iterator	operator-(difference_type n){return _cur_elem + n;}
			rev_iterator	&operator++(){--_cur_elem; return *this;}
			rev_iterator	&operator--(){++_cur_elem; return *this;}
			rev_iterator	&operator++(int){
				rev_iterator tmp(_cur_elem);
				--_cur_elem;
				return *this;
			}
			rev_iterator	&operator--(int){
				rev_iterator tmp(_cur_elem);
				++_cur_elem;
				return tmp;
			}
		private:
			pointer	_cur_elem;
				
	};

	template <typename LIter, typename RIter>
	typename work_whene_both_are_iter<typename LIter::my_rev_diff_type, typename RIter::my_rev_diff_type>::type
	operator-(const LIter &_lhs, const RIter &_rhs)
	{
		return  _rhs.base() - _lhs.base();
	}

	template <typename Iter>
	Iter	operator+(typename Iter::my_rev_diff_type n, Iter i)
	{
		i += n;
		return i;
	}
	template <typename LIter, typename RIter>
	typename LIter::my_rev_bool operator<(const LIter &a, const RIter &b)
	{
		return !(a.base() < b.base());
	}
	template <typename LIter, typename RIter>
	typename LIter::my_rev_bool operator<=(const LIter &a, const RIter &b)
	{
		return !(a.base() <= b.base());
	}
	template <typename LIter, typename RIter>
	typename LIter::my_rev_bool operator>(const LIter &a, const RIter &b)
	{
		return !(a.base() > b.base());
	}
	template <typename LIter, typename RIter>
	typename LIter::my_rev_bool operator>=(const LIter &a, const RIter &b)
	{
		return !(a.base() >= b.base());
	}
	template <typename LIter, typename RIter>
	typename LIter::my_rev_bool operator==(const LIter &a, const RIter &b)
	{
		return a.base() == b.base();
	}
	template <typename LIter, typename RIter>
	typename LIter::my_rev_bool operator!=(const LIter &a, const RIter &b)
	{
		return a.base() != b.base();
	}
};

#endif
