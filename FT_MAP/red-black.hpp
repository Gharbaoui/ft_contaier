#ifndef RED_BLACK
#define RED_BLACK


template <typename Value_type, typename Comp, typename Alloc>
class RB_tree{
	public:
		RB_tree() : root(NULL) {}
		~RB_tree() {}
	private:
		struct	node
		{
			node() : left(NULL), right(NULL) , color(true) {}
			Value_type	item;
			Value_type	*left;
			Value_type	*right;
			Value_type	*parent;
			bool		color; // true represent red false black
		};

		node	*root;

};

#endif
