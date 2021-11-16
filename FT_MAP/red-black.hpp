#ifndef RED_BLACK
#define RED_BLACK


template <typename Value_type, typename Key_compare, typename Alloc>
class RB_tree{
	public:
		RB_tree() : root(NULL)  {}
		struct	node
		{
			node() : left(NULL), right(NULL) , color(true) {}
			node(const Value_type &itm) : item(itm), left(NULL), right(NULL) , color(true) {}
		
        	Value_type	item;
			node        *left;
			node        *right;
			node        *parent;
			bool		color; // true represent red false black
		};
        void    insert(const Value_type &new_item)
        {
            node *n;
            if (find_help(new_item, root))
                return ;
            n = _node_alloc.allocate(1);
            _node_alloc.construct(n, new_item);
            if (root)
            {
                insert_help(n, root);
                if (n->parent->color)
                    solve_color_violation(n);
            }
            else
            {
                root = n;
                n->color = false;
                n->parent = NULL;
            }
            root->color = false;
        }

        void    rb_delete(const Value_type &v)
        {
            node *n = find_help(v, root);
            if (n)
                delete_help(n, root);
        }
    
        void    display()
        {
            int h;
            traversal(root);
            h = black_height(root);
            if (!root->color)
                --h;

            std::cout << "black height: " << h << std::endl;
        }
		~RB_tree() {}
	private:
        void    insert_help(node *n, node *head)
        {
            if (node_compare(n, head))
            {
                if (head->left)
                    insert_help(n, head->left);
                else
                {
                    head->left = n;
                    n->parent = head;
                }
            }
            else
            {
                if (head->right)
                    insert_help(n, head->right);
                else
                {
                    head->right = n;
                    n->parent = head;
                }
            }
        }
        node    *find_help(const Value_type item, node *head)
        {
            if (head)
            {
                if (_cmp(item.first, head->item.first))
                    return find_help(item, head->left);
                else if (item.first == head->item.first)
                    return head;
                else
                    return find_help(item, head->right);
            }
            else
                return NULL;
        }
        

        bool    node_compare(node *n1, node *n2)
        {
            // uses as  < operator
            return _cmp(n1->item.first, n2->item.first);
        }

        void    traversal(node *n)
        {
            if (n->left)
                traversal(n->left);
            if (!n->color)
                std::cout << "\033[0;30;107m";
            else
                std::cout << "\033[1;31;49m";
            std::cout << n->item.first << ": " << n->item.second << " color: " << n->color << std::endl;
            std::cout << "\033[0;39;49m";
            if (n->right)
                traversal(n->right);
        }

        bool    left_of(node *p, node *n)
        {
            if (p->left == n)
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

        bool    right_of(node *p, node *n)
        {
            if (p->right == n)
                return true;
            return false;
        }

        node    *successor(node *n)
        {
            node *tmp;

            tmp = NULL;
            if (n)
            {
                if (n->right)
                {
                    tmp = n->right;
                    while (tmp->left)
                        tmp = tmp->left;
                }
                else if (n->parent)
                {
                    tmp = n->parent;
                    if (tmp && left_of(tmp, n))
                        return tmp;
                    while (tmp && right_of(tmp->parent, tmp))
                        tmp = tmp->parent;
                    if (tmp)
                        tmp = tmp->parent;
                }
            }
            return tmp;
        }
        
        node    *predecessor(node *n)
        {
            node *tmp;

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
                    if (tmp && right_of(tmp, n))
                        return tmp;
                    while (tmp && left_of(tmp->parent, tmp))
                        tmp = tmp->parent;
                    if (tmp)
                        tmp = tmp->parent;
                }
            }
            return tmp;
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
                    u->color = p->color = false;
                    p->parent->color = true;
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
                        p->color = false;
                        p->parent->color = true;
                        left_rotation(p->parent);
                    }
                    else
                    {
                        if (right_of(p, tmp))
                        {
                            left_rotation(p);
                            p = tmp;
                        }
                        p->color = false;
                        p->parent->color = true;
                        right_rotation(p->parent);
                    }
                    break ;
                }
            }
        }

        bool    get_color(node *n)
        {
            if (n)
                return n->color;
            return false;
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


        void    delete_help(node *n, node *head)
        {
            std::cout << "node: " << n->item.first << std::endl;
            node *ns = successor(n);
            node *ps = predecessor(n);
            if (ns)
                std::cout << "successor: " << ns->item.first << std::endl;
            else
                std::cout << "no successor" << std::endl;
            if (ps)
                std::cout << "predecessor: " << ps->item.first << std::endl;
            else
                std::cout << "no predecessor: " << std::endl;
        }
    private:
		node	*root;
        Key_compare    _cmp;
        typename Alloc::template rebind<node>::other _node_alloc;

};

#endif
