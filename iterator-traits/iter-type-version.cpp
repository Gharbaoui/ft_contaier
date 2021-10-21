#ifndef	ITERATOR_HPP
#define	ITERATOR_HPP

namespace ft
{

	template <typename T, typename D=ptrdiff_t>
	class	random_access_iterator  {
		public:
			typedef	ft::random_access_iterator_tag	iterator_category;
			typedef	D								difference_type;
			typedef	T								value_type;
			typedef	value_type*						pointer;
			typedef	value_type&						reference;
			// init
			random_access_iterator() : _cul_elm(NULL) {}
			random_access_iterator(pointer p) : _cul_elm(p) {}
			random_access_iterator(const random_access_iterator &cp) : _cul_elm(cp._cul_elm){}
			random_access_iterator	&operator=(const random_access_iterator &rhs)
			{
				if (this != &rhs)
					_cul_elm = rhs._cul_elm;
				return *this;
			}
			/*
			// elment access
			reference	operator*() const {return *_cul_elm;}
			pointer		operator->() const {return _cul_elm;}
			reference	operator[](difference_type n) const {return *(_cul_elm + n);}
			// arithmetic operations
			random_access_iterator	&operator+=(difference_type n)
			{
				_cul_elm += n;
				return *this;
			}
			random_access_iterator	&operator-=(difference_type n)
			{
				_cul_elm -= n;
				return *this;
			}
			random_access_iterator	operator+(difference_type n)
			{
				return (_cul_elm + n);
			}
			random_access_iterator	operator-(difference_type n)
			{
				return (_cul_elm - n);
			}
			difference_type			operator-(const random_access_iterator &rhs)
			{
				return _cul_elm - rhs._cul_elm;
			}
			// compare operations
			bool	operator<(const random_access_iterator &a)
			{
				return _cul_elm < a._cul_elm;
			}
			bool	operator<=(const random_access_iterator &a)
			{
				return _cul_elm <= a._cul_elm;
			}
			bool	operator>(const random_access_iterator &a)
			{
				return _cul_elm > a._cul_elm;
			}
			bool	operator>=(const random_access_iterator &a)
			{
				return _cul_elm >= a._cul_elm;
			}
			bool	operator==(const random_access_iterator &a)
			{
				return _cul_elm == a._cul_elm;
			}
			bool	operator!=(const random_access_iterator &a)
			{
				return _cul_elm != a._cul_elm;
			}*/
		private:
			pointer	_cul_elm;
	};
	template <typename T , typename D>
	random_access_iterator<T, D> operator+(typename random_access_iterator<T, D>::difference_type n,
	random_access_iterator<T, D> i){
		i += n;
		return i;
	}
};

#endif
