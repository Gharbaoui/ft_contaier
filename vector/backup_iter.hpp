#ifndef	ITERATOR_HPP
#define ITERATOR_HPP

namespace ft{
	template <typename PT>
	class	random_access_iterator {
		public:
			typedef	typename iterator_traits<PT>::value_type			value_type;
			typedef	typename iterator_traits<PT>::iterator_category		iterator_category;
			typedef	typename iterator_traits<PT>::difference_type		difference_type;
			typedef	typename iterator_traits<PT>::pointer				pointer;
			typedef	typename iterator_traits<PT>::reference				reference;
			typedef	bool												is_iter;
			typedef	bool												is_join_iter;
			random_access_iterator() : _cur_elm(NULL) {}
			random_access_iterator(pointer p) : _cur_elm(p){}
			random_access_iterator(const random_access_iterator &cp) : _cur_elm(cp._cur_elm) {}
			random_access_iterator	&operator=(const random_access_iterator &rhs)
			{
				if (this != &rhs)
					_cur_elm = rhs._cur_elm;
				return *this;
			}
			template <typename Iter> // this will make const_iter from iter
			random_access_iterator(const Iter &i, typename Iter::is_iter=true) : _cur_elm(i.base()) {}
			pointer	base() const {return _cur_elm;}

			reference	operator*() const {return *_cur_elm;}
			pointer		operator->() const {return _cur_elm;}
			reference	operator[](size_t index) const {return *(_cur_elm + index);}

			// arithmetic operations
			random_access_iterator	&operator+=(difference_type n){_cur_elm += n; return *this;}
			random_access_iterator	&operator-=(difference_type n){_cur_elm -= n; return *this;}
			random_access_iterator	operator+(difference_type n){return _cur_elm + n;}
			random_access_iterator	operator-(difference_type n){return _cur_elm - n;}
			random_access_iterator	&operator++(){++_cur_elm; return *this;}
			random_access_iterator	&operator--(){--_cur_elm; return *this;}
			random_access_iterator	operator++(int){
				random_access_iterator tmp(_cur_elm);
				++_cur_elm;
				return tmp;
			}
			random_access_iterator	operator--(int){
				random_access_iterator tmp(_cur_elm);
				--_cur_elm;
				return tmp;
			}
		private:
			pointer	_cur_elm;

	};
	template <typename LIter, typename RIter> // difference between two operators
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value,
							typename LIter::difference_type
	>::type
	operator - (const LIter &lsh, const RIter &rhs){
		return lsh.base() - rhs.base();
	}

	template <typename Iter>
	typename ft::enable_if<ft::has_type<typename Iter::is_iter>::value, Iter>::type
	operator + (typename Iter::difference_type n, Iter i)
	{
		i += n;
		return i;
	}
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator < (const LIter &lsh, const RIter &rhs){
		return lsh.base() < rhs.base();
	}

	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator > (const LIter &lsh, const RIter &rhs){
		return !(lsh < rhs);
	}
	
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator <= (const LIter &lsh, const RIter &rhs){
		return lsh.base() <= rhs.base();
	}
	
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator >= (const LIter &lsh, const RIter &rhs){
		return lsh.base() >= rhs.base();
	}
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator == (const LIter &lsh, const RIter &rhs){
		return lsh.base() == rhs.base();
	}
	
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_iter, typename RIter::is_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator != (const LIter &lsh, const RIter &rhs){
		return lsh.base() != rhs.base();
	}
};


// reverse iterator can be constructed from iterator and not via only explicit construction assigment operator
// oppsite is not
//
namespace ft{
	template <typename PT>
	class	reverse_iterator {
		public:
			typedef	typename iterator_traits<PT>::value_type			value_type;
			typedef	typename iterator_traits<PT>::iterator_category		iterator_category;
			typedef	typename iterator_traits<PT>::difference_type		difference_type;
			typedef	typename iterator_traits<PT>::pointer				pointer;
			typedef	typename iterator_traits<PT>::reference				reference;
			typedef	bool												is_reverse_iter;
			typedef	bool												is_join_iter;
			reverse_iterator() : _cur_elm(NULL) {}
			reverse_iterator(pointer p) : _cur_elm(p - 1) {}
			reverse_iterator(const reverse_iterator &cp) : _cur_elm(cp._cur_elm - 1) {}
			reverse_iterator	&operator=(const reverse_iterator &rhs)
			{
				if (this != &rhs)
					_cur_elm = rhs._cur_elm;
				return *this;
			}
			// as you may see here i m not decreasing by one bec this will called after tmp created and in action to create tmp then decreas will happen
			// copy elsion
			template <typename Iter> // this will make const_rev_iter from rev_iter possible
			explicit reverse_iterator(const Iter &i) : _cur_elm(i.base()) {}
		
			template <typename Iter>
			typename ft::enable_if<has_type<typename Iter::is_reverse_iter>::value, reverse_iterator&>::type
			operator=(const Iter &rhs)
			{
				// i dont use here (this != &rhs) bec if this is called means that it can't be the same type even 
				// if that is the case normal = operator will be used this one is for const_iter to iter
				_cur_elm = rhs.base();
				return *this;
			}
			pointer	base() const {return _cur_elm;}
			
			reference	operator*() const {return *_cur_elm;}
			pointer		operator->() const {return _cur_elm;}
			reference	operator[](size_t index) const {return *(_cur_elm - index);}

			// arithmetic operations
			reverse_iterator	&operator+=(difference_type n){_cur_elm -= n; return *this;}
			reverse_iterator	&operator-=(difference_type n){_cur_elm += n; return *this;}
			reverse_iterator	operator+(difference_type n){return _cur_elm - n;}
			reverse_iterator	operator-(difference_type n){return _cur_elm + n;}
			reverse_iterator	&operator++(){--_cur_elm; return *this;}
			reverse_iterator	&operator--(){++_cur_elm; return *this;}
			reverse_iterator	operator++(int){
				reverse_iterator tmp(_cur_elm);
				--_cur_elm;
				return tmp;
			}
			reverse_iterator	operator--(int){
				reverse_iterator tmp(_cur_elm);
				++_cur_elm;
				return tmp;
			}
		private:
			pointer	_cur_elm;

	};
	template <typename LIter, typename RIter> // difference between two operators
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value,
							typename LIter::difference_type
	>::type
	operator - (const LIter &lhs, const RIter &rhs){
		return rhs.base() - lhs.base();
	}

	template <typename Iter>
	typename ft::enable_if<ft::has_type<typename Iter::is_reverse_iter>::value, Iter>::type
	operator + (typename Iter::difference_type n, Iter i)
	{
		i += n;
		return i;
	}
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator < (const LIter &lhs, const RIter &rhs){
		return rhs.base() < lhs.base();
	}

	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator > (const LIter &lhs, const RIter &rhs){
		return !(lhs < rhs);
	}
	
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator <= (const LIter &lhs, const RIter &rhs){
		return rhs.base() <= lhs.base();
	}
	
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator >= (const LIter &lhs, const RIter &rhs){
		return rhs.base() >= lhs.base();
	}
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator == (const LIter &lhs, const RIter &rhs){
		return lhs.base() == rhs.base();
	}
	
	
	template <typename LIter, typename RIter>
	typename ft::enable_if<
							std::is_same<typename LIter::is_reverse_iter, typename RIter::is_reverse_iter>::value &&
							std::is_same<typename LIter::value_type, typename RIter::value_type>::value
	>::type
	operator != (const LIter &lhs, const RIter &rhs){
		return lhs.base() != rhs.base();
	}
};
#endif
