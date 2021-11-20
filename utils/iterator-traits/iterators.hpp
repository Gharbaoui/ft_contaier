#ifndef ITERATOR
#define ITERATOR

namespace ft
{
	template <typename Iter> // Iter could be iterator or just pointer
	class random_access_iterator{
		public:
			typedef	Iter													iterator_type;
			typedef	typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef	typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef	typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef	typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef	typename ft::iterator_traits<Iter>::reference			reference;

			//default constructor
			//set _cur_iter to it's default in case of pointer set it to nullptr
			random_access_iterator() : _cur_iter(iterator_type()) {}
			// this constructor will allow you to pass Iter obj not random_access_iterator and still construct
			// example
			// Iter o;
			// random_access_iterator<some::Iter> l(o); will posiible
		//	ft::vector<int>::iterator k; is type (A) for example has inside int*
		//	ft::random_access_iterator<ft::vector<int>::iterator> kl(k); this is other type but still can be constructed fron type (A)
			random_access_iterator(const Iter &iter) : _cur_iter(iter) {}
			// copy constructor
			random_access_iterator(const random_access_iterator &cp) : _cur_iter(cp.base()) {}
			random_access_iterator &operator=(const random_access_iterator &rhs)
			{
				if (this != &rhs)
					_cur_iter = rhs.base();
				return *this;
			}
			// this template will allow you to construct const_iterator to iterator
			// const int -> int is ok
			// int ->const int not ok
			// for example
			// random_access_iterator<int *> l;
			// random_access_iterator<const int *> k(l); will work
			// bec this is not explicit this will be called in assigmnt operator
			template <typename Iter_To_CI>
			random_access_iterator (const random_access_iterator<Iter_To_CI> &iter,
			typename ft::enable_if<ft::can_inter_change<Iter_To_CI, iterator_type>::value>::type=false)
			: _cur_iter(iter.base()) {}
			iterator_type const &base() const {return _cur_iter;}

			reference				operator*() const {return *_cur_iter;}
			pointer					operator->() const {return _cur_iter;}

			random_access_iterator&	operator++() { ++_cur_iter; return *this; }
			random_access_iterator	operator++(int) { return random_access_iterator(_cur_iter++); }
			
			random_access_iterator&	operator--() { --_cur_iter; return *this; }
			random_access_iterator	operator--(int) { return random_access_iterator(_cur_iter--); }

			reference				operator[](difference_type n) const { return _cur_iter[n]; }
			random_access_iterator	&operator+=(difference_type n) { _cur_iter += n; return *this; }
			random_access_iterator	&operator-=(difference_type n) { _cur_iter -= n; return *this; }
			random_access_iterator	operator+(difference_type n) const { return random_access_iterator(_cur_iter + n); }
			random_access_iterator	operator-(difference_type n) const { return random_access_iterator(_cur_iter - n); }
		private:
			iterator_type	_cur_iter;
	};
	// this will allow operations between iterator and const_iterator
	template <typename LIter, typename RIter>
	typename ft::iterator_traits<LIter>::difference_type
	operator-(const ft::random_access_iterator<LIter> &lhs, const ft::random_access_iterator<RIter> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename LIter, typename RIter>
	bool	operator==(const ft::random_access_iterator<LIter> &lhs, const random_access_iterator<RIter> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename LIter, typename RIter>
	bool	operator!=(const ft::random_access_iterator<LIter> &lhs, const random_access_iterator<RIter> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename LIter, typename RIter>
	bool	operator<(const ft::random_access_iterator<LIter> &lhs, const random_access_iterator<RIter> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename LIter, typename RIter>
	bool	operator<=(const ft::random_access_iterator<LIter> &lhs, const random_access_iterator<RIter> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename LIter, typename RIter>
	bool	operator>(const ft::random_access_iterator<LIter> &lhs, const random_access_iterator<RIter> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename LIter, typename RIter>
	bool	operator>=(const ft::random_access_iterator<LIter> &lhs, const random_access_iterator<RIter> &rhs)
	{
		return lhs.base() >= rhs.base();
	}



	template<typename Iter>
	ft::random_access_iterator<Iter>
	operator+(typename ft::iterator_traits<Iter>::difference_type n,
	ft::random_access_iterator<Iter> iter)
	{
		iter += n;
		return iter;
	}

	template <typename Iter>
	class reverse_iterator{
		public:
			typedef	Iter													iterator_type;
			typedef	typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef	typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef	typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef	typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef	typename ft::iterator_traits<Iter>::reference			reference;
			//default constructor
			reverse_iterator() : current(iterator_type()) {}
			reverse_iterator(const reverse_iterator &cp) : current(cp.current) {}
			template<class _Iter>
			reverse_iterator& operator=(const reverse_iterator<_Iter>& other)
			{
				current = other.base();
				return *this;
			}
			// construct from Iter Obj not reverse_iterator
			// std::..::iterator k;
			// std::reverse_iterator<std::..::iterator> l(k); possible
			explicit	reverse_iterator(const iterator_type &iter_obj) : current(iter_obj) {}
			// construct const_rev_iter from rev_iter
			template<typename _Iter>
			reverse_iterator(const reverse_iterator<_Iter>& iter) : current (iter.base()) {}
			iterator_type	base() const {return current;}
			reference		operator*() const {
				iterator_type tmp(current);
				--tmp;
				return *tmp;
			}
			pointer			operator->() const {
				iterator_type tmp(current); 
				--tmp;
				return  tmp.operator->(); // calling -> op of iterator_type;
			}

			reverse_iterator&	operator++() { --current; return *this; }
			reverse_iterator&	operator--() { ++current; return *this; }
			reverse_iterator	operator++(int) {
				reverse_iterator tmp(current);
				--current;
				return tmp;
			}
			reverse_iterator	operator--(int) {
				reverse_iterator tmp(current);
				++current;
				return tmp;
			}
			reference				operator[](difference_type n) const {
				int a = *(current - 1);
				iterator_type tmp(current - (n + 1));
				return *tmp; // return lmenr
			}
			reverse_iterator	operator+(difference_type n) const
			{
				reverse_iterator tmp(current - n);
				return tmp;
			}
			
			reverse_iterator	operator-(difference_type n) const
			{
				reverse_iterator tmp(current + n);
				return tmp;
			}
			reverse_iterator&	operator-=(difference_type n)
			{
				current += n;
				return *this;
			}
			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return *this;
			}
		private:
			iterator_type	current;

	};
	template <typename LIter, typename RIter>
	typename ft::iterator_traits<LIter>::difference_type
	operator-(const ft::reverse_iterator<LIter> &lhs, const ft::reverse_iterator<RIter> &rhs)
	{
		return rhs.base() - lhs.base();
	}
	/// add operators
	template<typename LIter, typename RIter >
	bool operator==(const ft::reverse_iterator<LIter>& lhs, const ft::reverse_iterator<RIter>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	
	template<typename LIter, typename RIter >
	bool operator!=(const ft::reverse_iterator<LIter>& lhs, const ft::reverse_iterator<RIter>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	
	template<typename LIter, typename RIter >
	bool operator<(const ft::reverse_iterator<LIter>& lhs, const ft::reverse_iterator<RIter>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	
	template<typename LIter, typename RIter >
	bool operator>(const ft::reverse_iterator<LIter>& lhs, const ft::reverse_iterator<RIter>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	
	template<typename LIter, typename RIter >
	bool operator>=(const ft::reverse_iterator<LIter>& lhs, const ft::reverse_iterator<RIter>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
	
	template<typename LIter, typename RIter >
	bool operator<=(const ft::reverse_iterator<LIter>& lhs, const ft::reverse_iterator<RIter>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename RIter>
	ft::reverse_iterator<RIter>
	operator+(typename ft::iterator_traits<RIter>::difference_type n, ft::reverse_iterator<RIter> i)
	{
		i += n;
		return i;
	}
};





#endif
