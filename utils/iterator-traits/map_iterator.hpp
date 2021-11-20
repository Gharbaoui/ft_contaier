#ifndef MAP_ITERATOR
#define MAP_ITERATOR

namespace ft
{

template <typename VT> // VT value_type

class rb_iterator{
    public:
        typedef VT                              value_type;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef VT*                             pointer;
        typedef VT&                             reference;

        typedef RB_node<value_type>             node;

        // constructors
        rb_iterator() : current(NULL) {}
        rb_iterator(node *n) : current(n) {}
        rb_iterator(const rb_iterator &cp) : current(cp.current) {}

        reference operator*() const {return current->get_item();}
        pointer operator->() const {return &current->get_item();}
    private:
        node    *current;
        
};

}
#endif
