#ifndef MAP_ITERATOR
#define MAP_ITERATOR

namespace ft
{

template <typename VT, typename RFER, typename POINTER, typename Alloc>
class rb_iterator{
	private:
		typedef	rb_iterator<VT, VT const &, VT const *, Alloc>	const_iterator;
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

		operator const_iterator()
		{
			return const_iterator(current, last_node, most_node);
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

		bool	operator==(const rb_iterator &rhs) {return current == rhs.current;}
		bool	operator!=(const rb_iterator &rhs) {return current != rhs.current;}

        node    *get_current() const {return current;}
	private:
        node		*current;
		node		*last_node;
		node		*most_node;
		typename Alloc::template rebind<node>::other		_alloc;
        
};

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
		
        bool	operator==(const reverse_iterator &rhs)
        {return current_itr == rhs.current_it;}
        
		bool	operator!=(const reverse_iterator &rhs)
        {return current_itr != rhs.current_itr;}
        
	private:
		iterator_type	current_itr;
};
}
#endif
