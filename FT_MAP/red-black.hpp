#ifndef RED_BLACK
#define RED_BLACK


template <typename Value_type, typename Comp, typename Alloc>
class RB_tree{
	public:
		struct	node
		{
			node() : left(NULL), right(NULL) , color(true) {}
			Value_type	item;
			Value_type	*left;
			Value_type	*right;
			Value_type	*parent;
			bool		color; // true represent red false black
		};
		RB_tree() : root(NULL) {}
        void    insert(const Value_type &new_item)
        {
            node    *n;
        }
		~RB_tree() {}
	private:

		node	*root;
        Comp    _cmp;
        Alloc   _mem;

};

#endif
