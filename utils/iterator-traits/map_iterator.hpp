#ifndef MAP_ITERATOR
#define MAP_ITERATOR

namespace ft
{

template <typename VT, typename RFER, typename POINTER, typename Alloc>
class rb_iterator{
    public:
        typedef VT                              value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef POINTER                         pointer;
        typedef RFER  		                    reference;

        typedef RB_node<value_type>             node;

        // constructors
        rb_iterator() : current(NULL) {
			last_node = _alloc.allocate(1);
		}
        rb_iterator(node *n, node *last_n, node *right_m) :
		current(n) , last_node(last_n), most_node(right_m) {}

        rb_iterator(const rb_iterator &cp) :
		current(cp.current) , last_node(cp.last_node), most_node (cp.most_node) {}
		
		template <typename R1, typename P1>
		rb_iterator(const rb_iterator<VT, R1, P1, Alloc> &iter)
		{
			// if P1 is pointer to const below function
			// is formed
			// if not it's ill-formed and it will fail to compile
			// this will allow from iter =? to const iter
			// and from const iter => iter
			help_constr_iter_to_const_iter<P1>();
			current = iter.get_current();
			last_node = iter.get_last_node();
			most_node = iter.get_most_node();
		}
		rb_iterator&	operator=(const rb_iterator &rhs)
		{
			if (this != &rhs)
			{
				current = rhs.current;
				last_node = rhs.last_node;
				most_node = rhs.most_node;
			}
			return *this;
		}

        reference operator*() const {return current->get_item();}
        pointer operator->() const {return &current->get_item();}


		rb_iterator&	operator++()
		{
            if (current == last_node)
            {
                current = NULL;
            }
            else if (current)
            {
                current = current->successor();
                if (!current)
                    current = last_node;
            }
			return *this;
		}

		rb_iterator&	operator--()
		{
            if (current == last_node)
            {
                current = most_node;
            } else if (current)
            {
                current = current->predecessor();
            }
			return *this;
		}

		rb_iterator	operator--(int)
		{
			rb_iterator	tmp(*this);
			operator--();
			return tmp;
		}

		rb_iterator	operator++(int)
		{
			rb_iterator	tmp(*this);
			operator++();
			return tmp;
		}

        node    *get_current() const {return current;}
        node    *get_last_node() const {return last_node;}
        node    *get_most_node() const {return most_node;}
	private:
        node		*current;
		node		*last_node;
		node		*most_node;
		typename Alloc::template rebind<node>::other		_alloc;

	private:
		template <typename T>
		void	help_constr_iter_to_const_iter(
		typename ft::enable_if<!ft::p_to_const<T>::value>::type=false		
		)
		{
			// this function does nothing
			// but magic in one he use it
		}
        
};

template <typename VT, typename R1, typename R2, typename P1, typename P2, typename Al>
bool	operator==(const rb_iterator<VT, R1, P1, Al> &lhs, const rb_iterator<VT, R2, P2, Al> &rhs)
{
	return lhs.get_current() == rhs.get_current();
}

template <typename VT, typename R1, typename R2, typename P1, typename P2, typename Al>
bool	operator!=(const rb_iterator<VT, R1, P1, Al> &lhs, const rb_iterator<VT, R2, P2, Al> &rhs)
{
	return lhs.get_current() != rhs.get_current();
}
/*
template <typename ITER>
class	reverse_iterator{
	public:
		typedef	ITER													iterator_type;
		typedef	typename ft::iterator_traits<ITER>::value_type			value_type;
		typedef	typename ft::iterator_traits<ITER>::difference_type		difference_type;
		typedef	typename ft::iterator_traits<ITER>::iterator_category	iterator_category;
		typedef	typename ft::iterator_traits<ITER>::reference			reference;
		typedef	typename ft::iterator_traits<ITER>::pointer				pointer;

		reverse_iterator() : current_itr() {}
		reverse_iterator(const iterator_type &itr) : current_itr(itr) {}
		reverse_iterator(const reverse_iterator &riter) : current_itr(riter.current_itr) {}
		reverse_iterator &operator=(const reverse_iterator &rhs)
		{
			if (this != &rhs)
				current_itr = rhs.current_itr;
			return *this;
		}
		template <typename CITER>
		reverse_iterator(const reverse_iterator<CITER> &citr) : current_itr(citr.base()) {}

		iterator_type	base() const {return   current_itr;}
		reference	operator*() const {
            iterator_type tmp(current_itr);
            --tmp;
            return *tmp;
        }

        pointer operator->() const {
            return &(operator*());
        }

		reverse_iterator&	operator++()
		{
            --current_itr;
			return *this;
		}

		reverse_iterator&	operator--()
		{
			++current_itr;
			return *this;
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator tmp(*this);
			operator--();
			return tmp;
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator tmp(*this);
			operator++();
			return tmp;
		}
	private:
		iterator_type	current_itr;
};

template <typename LITER, typename RITER>
bool	operator==(const ft::reverse_iterator<LITER> &lhs, const ft::reverse_iterator<RITER> &rhs)
{
	return lhs.base() == rhs.base();
}

template <typename LITER, typename RITER>
bool	operator!=(const ft::reverse_iterator<LITER> &lhs, const ft::reverse_iterator<RITER> &rhs)
{
	return lhs.base() != rhs.base();
}*/

}
#endif
