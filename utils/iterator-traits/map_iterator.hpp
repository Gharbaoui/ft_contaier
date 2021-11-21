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
        rb_iterator(node *n, node *last_n) :
		current(n) , last_node(last_n), right_most(NULL) {}
        rb_iterator(node *n, node *last_n, node *right_m) :
		current(n) , last_node(last_n), right_most(right_m) {}

        rb_iterator(const rb_iterator &cp) :
		current(cp.current) , last_node(cp.last_node), right_most (cp.right_most) {}
		
		rb_iterator&	operator=(const rb_iterator &rhs)
		{
			if (this != &rhs)
			{
				current = rhs.current;
				last_node = rhs.last_node;
				right_most = rhs.right_most;
			}
			return *this;
		}

		operator const_iterator()
		{
			return const_iterator(current, last_node, right_most);
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
				current = right_most;
			}
			else if (current)
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

	private:
        node		*current;
		node		*last_node;
		node		*right_most;
		typename Alloc::template rebind<node>::other		_alloc;
        
};
}
#endif
