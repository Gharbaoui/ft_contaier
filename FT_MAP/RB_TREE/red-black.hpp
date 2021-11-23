#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE

namespace   ft
{
    typedef enum
    {
        red = true,
        black = false
    } node_color;

    template <typename ITEM_TYPE>
    struct   RB_node
    {
        RB_node() {
            color = red;
            left = NULL;
            right = NULL;
        }

        RB_node(const ITEM_TYPE &v) : item(v) {
            color = red;
            left = right = NULL;
        }

		RB_node	&operator=(const RB_node &rhs)
		{
			if (this != &rhs)
			{
				item = rhs.item;
				color = rhs.color;
				left = rhs.left;
				right = rhs.right;
				parent = rhs.parent;
			}
			return *this;
		}

        ITEM_TYPE   item;
        node_color  color;
        RB_node     *left;
        RB_node     *right;
        RB_node     *parent;

        static  RB_node *successor(RB_node *n)
        {
            RB_node *tmp;

            tmp = NULL;
            if (n)
            {
                if (n->right)
                {
                    tmp  = n->right;
                    while (tmp->left)
                        tmp = tmp->left;
                }
                else if (n->parent)
                {
                    tmp  = n->parent;
                    if (tmp && tmp->left == n)
                        return tmp;
					if (!tmp->parent)
						return NULL;
                    while (tmp->parent && tmp->parent->right == tmp)
                        tmp = tmp->parent;
                    if (tmp)
                        tmp = tmp->parent;
                }
            }
            return tmp;
        }

        RB_node  *successor() {return RB_node::successor(this);}

        static RB_node  *predecessor(RB_node *n)
        {
            RB_node *tmp;

            tmp = NULL;
            if (n)
            {
                if (n->left)
                {
                    tmp = n->left;
                    while (tmp->right)
                        tmp = tmp->right;
                }else if (n->parent)
                {
                    tmp = n->parent;
                    if (tmp && tmp->right == n)
                        return tmp;
					if (!tmp->parent)
						return NULL;
                    while (tmp->parent && tmp->parent->left == tmp)
                        tmp = tmp->parent;
                    if (tmp)
                        tmp = tmp->parent;
                }
            }
            return tmp;
        }

        RB_node *predecessor() {return RB_node::predecessor(this);}

        ITEM_TYPE   &get_item() {return item;}
    };

    template <typename value_type, typename key_compare, typename key_type, typename alloc>
    class   RB_manager
    {
        public:
            typedef RB_node<value_type>    node;

            RB_manager() : root(NULL), size(0) {
				last_node = _n_alloc.allocate(1);
			}

            node    *insert(const value_type &v, bool &was_here, node *head=NULL)
            {
                node *n;
				was_here = false;
                n = find(v.first, root);
                if (n) {
                	was_here = true;
					return n;
				}
				if (!head)
					head = root;
				++size;
                n = _n_alloc.allocate(1);
                _n_alloc.construct(n, v);
                if (root)
                {
                    normal_insert(n, head, v.first);
                    if (n->parent->color == ft::red)
                        solve_color_violation(n);
                }
                else
                {
                    root = n;
                    n->parent = NULL;
                    n->color = black;
                }
                return n;
            }

			void	swap_rb_manager(RB_manager &other)
			{
				ft::swap(size, other.size);
				ft::swap(root, other.root);
				ft::swap(last_node, other.last_node);
				ft::swap(last_node, other.last_node);
				ft::swap(_cmp, other._cmp);
				ft::swap(_n_alloc, other._n_alloc);
			}
			
			node*	get_last_node() const
			{
				return last_node;
			}

			node *lower_bound(const key_type& key) const
			{
				// working here
			}

            void    remove_node(const key_type &k, node *cn=NULL)
            {
				node *n;
				if (!cn)
                	n = find(k, root);
				else
					n = cn;
                if (n) {
                    remove_node_help(n , root);
					--size;
				}
            }

            int bh()
            {
                int h;
                h = black_height(root);
                if (root->color == ft::black)
                    --h;
                return h;
            }

            int black_height(node *n)
            {
                int lh, rh;
                if (!n)
                    return 1;
                else {
                    lh = black_height(n->left);
                    rh = black_height(n->right);
                    if (lh != rh)
                        return -100000;
                    return lh + !n->color;
                }
            }

            node    *left_most(node *n) const
            {
                if (n)
                {
                    while (n->left)
                        n = n->left;
                }
                return n;
            }
			
			node	*left_most() const
			{
				node *n = left_most(root);
				return n ? n : last_node;
			}

            node    *right_most(node *n) const
            {
                if (n)
                {
                    while (n->right)
                        n = n->right;
                }
                return n;
            }
			
			node	*right_most() const
			{
				node *n = right_most(root);
				return n ? n : last_node;
			}


			bool	empty() const {return !root;}

           	size_t	get_size() const {return size;} 

			node	*find(const key_type& k) const
			{
				return find(k, root);
			}

        private:
            node    *BST_delete(node *n)
            {
                node *tmp;
                
                if (n->right)
                {
                    tmp = node::successor(n);
                    node_swap(n, tmp);
                    return BST_delete(n);
                }
                else if (n->left)
                {
                    tmp = node::predecessor(n);
                    node_swap(n, tmp);
                    return BST_delete(n);
                }
                else
                    return n;
            }
            
        
            void    remove_node_help(node *n, node *head)
            {
                node *tmp;
                node *sb, *neph, *niece;
                
                tmp = BST_delete(n);
                while (1)
                {
                    if (!tmp->parent)
                        break ;
                    else if (tmp->color == ft::red) // red node
                        break ;
                    else
                    {
                        sb = sibling_of(tmp);
                        neph = nephew_of(tmp);
                        niece = niece_of(tmp);
                        if (get_color(sb) == ft::black) // black sibling
                        {
                            if (get_color(neph) == ft::red)
                            {
                                sb->color = tmp->parent->color;
                                tmp->parent->color = ft::black;
                                neph->color = ft::black;
                                rotate_sibling_to_parent(tmp->parent, sb);
                                break ;
                            }
                            else if (get_color(niece) == ft::red)
                            {
                                niece->color = ft::black;
                                sb->color = ft::red;
                                rotate_niece_to_sibling(sb, niece);
                            }
                            else
                            {
                                sb->color = ft::red;
                                tmp = tmp->parent;
                            }
                        }
                        else
                        {
                            tmp->parent->color = ft::red;
                            sb->color = ft::black;
                            rotate_sibling_to_parent(tmp->parent, sb);
                        }
                    }
                }
                if (tmp)
                    tmp->color = ft::black;
                put_in_my_place(n);
               _n_alloc.deallocate(n, 1);
                _n_alloc.destroy(n);
            }
        // helper functions
            // insert help
            node    *find(key_type key, node *head) const
            {
                while (head)
                {
                    if (_cmp(key, head->item.first))
                        head = head->left;
                    else if (key == head->item.first)
                        return head;
                    else
                        head = head->right;
                }
                return head;
            }

            void    normal_insert(node *n, node *head, key_type key)
            {
                while (head)
                {
                    if (_cmp(key, head->item.first))
                    {
                        if (head->left)
                            head = head->left;
                        else
                        {
                            head->left = n;
                            n->parent = head;
                            break ;
                        }
                    }
                    else
                    {
                        if (head->right)
                            head = head->right;
                        else
                        {
                            head->right = n;
                            n->parent = head;
                            break ;
                        }
                    }
                }
            }

            bool    get_color(node *n)
            {
                if (n)
                    return n->color;
                return ft::black;
            }

            void    left_rotation(node *n)
            {
                node *tmp;

                tmp = n->right;
                n->right = tmp->left;
                if (n->right)
                    n->right->parent = n;
                tmp->left = n;
                if (n->parent)
                {
                    if (left_of(n->parent, n))
                        n->parent->left = tmp;
                    else
                        n->parent->right = tmp;
                }
                else
                    root = tmp;
                tmp->parent = n->parent;
                n->parent = tmp;
            }

            void    right_rotation(node *n)
            {
                node *tmp;

                tmp = n->left;
                n->left = tmp->right;
                if (n->left)
                    n->left->parent = n;
                tmp->right = n;
                if (n->parent)
                {
                    if (left_of(n->parent, n))
                        n->parent->left = tmp;
                    else
                        n->parent->right = tmp;
                }
                else
                    root = tmp;
                tmp->parent = n->parent;
                n->parent = tmp;
            }

            void    swap_children(node *a, node *b)
            {
                node    *bs;
                node    *as;

                as = a->left;
                bs = b->left;

                b->left = as;
                if (as)
                    as->parent = b;
                a->left = bs;
                if (bs)
                    bs->parent = a;

                as = a->right;
                bs = b->right;

                b->right = as;
                if (as)
                    as->parent = b;
                a->right = bs;
                if (bs)
                    bs->parent = a;
            }

            void    swap_parent(node *a, node *b)
            {
                // b will always have parent
                node *ap;

                ap = a->parent;
                a->parent = b->parent;
                if (b->parent->left == b)
                    a->parent->left = a;
                else
                    a->parent->right = a;
                b->parent = ap;
                if (ap)
                {
                    if (ap->left == a)
                        ap->left = b;
                    else
                        ap->right = b;
                }
                else
                    root = b;
            }

            void    node_swap(node *a, node *b)
            {
                swap_children(a, b);
                if (b->parent)
                    swap_parent(a, b);
                else
                    swap_parent(b, a);
                std::swap(b->color, a->color);
            }

            bool    left_of(node *p, node *n)
            {
                if (p->left == n)
                    return true;
                return false;
            }

            bool    right_of(node *p, node *n)
            {
                if (p->right == n)
                    return true;
                return false;
            }

            node    *sibling_of(node *n)
            {
                if (n->parent) {
                    if (left_of(n->parent, n))
                        return n->parent->right;
                    else
                        return n->parent->left;
                }
                return NULL;
            }
            
            node    *nephew_of(node *n)
            {
                if (left_of(n->parent, n))
                {
                    if (n->parent->right)
                        return n->parent->right->right;
                    else
                        return NULL;
                }
                else
                {
                    if (n->parent->left)
                        return n->parent->left->left;
                    else
                        return NULL;
                }
            }

            node    *niece_of(node *n)
            {
                if (left_of(n->parent, n))
                {
                    if (n->parent->right)
                        return n->parent->right->left;
                    else
                        return NULL;
                }
                else
                {
                    if (n->parent->left)
                        return n->parent->left->right;
                    else
                        return NULL;
                }
            }

            void    rotate_sibling_to_parent(node *p, node *sb)
            {
                if (right_of(p, sb))
                    left_rotation(p);
                else
                    right_rotation(p);
            }
            
            void    rotate_niece_to_sibling(node *s, node *n)
            {
                if (left_of(s, n))
                    right_rotation(s);
                else
                    left_rotation(s);
            }

            void    put_in_my_place(node *n)
            {
                if (n)
                {
                    if (n->parent)
                    {
                        if (left_of(n->parent, n))
                            n->parent->left = NULL;
                        else
                            n->parent->right = NULL;
                    }
                    else
                        root = NULL;
                }
            }
        
            void    solve_color_violation(node *n)
            {
                node *p;
                node *u;
                node *tmp;

                tmp  = n;
                while (tmp && (p = tmp->parent) && get_color(p))
                {
                    u = sibling_of(tmp->parent);
                    if (get_color(u))
                    {
                        u->color = p->color = ft::black;
                        p->parent->color = ft::red;
                        tmp = p->parent;
                    }
                    else
                    {
                        if (right_of(p->parent, p))
                        {
                            if (left_of(p, tmp))
                            {
                                right_rotation(p);
                                p = tmp;
                            }
                            p->color = ft::black;
                            p->parent->color = ft::red;
                            left_rotation(p->parent);
                        }
                        else
                        {
                            if (right_of(p, tmp))
                            {
                                left_rotation(p);
                                p = tmp;
                            }
                            p->color = ft::black;
                            p->parent->color = ft::red;
                            right_rotation(p->parent);
                        }
                        break ;
                    }
                }
                root->color = ft::black;
            }
        private:
			size_t		size;
            key_compare _cmp;
            node        *root;
			node		*last_node;
            typename alloc::template rebind<node>::other    _n_alloc;
            
    };
};


#endif
