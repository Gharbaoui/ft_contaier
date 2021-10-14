#ifndef LIST_HPP
#define	LIST_HPP

template <typename T>
class	List{
	public:
		List(){
			head = tail = nullptr;
		}
		bool	isEmpty()
		{
			return head == nullptr;
		}
		class	List_Iterator{
			public:
				typedef std::ptrdiff_t difference_type;
				typedef std::forward_iterator_tag iterator_category;
				typedef T value_type;
				typedef T* pointer;
				typedef T& reference;
		};
		typedef	List_Iterator iterator;
	private:
		T	*head;
		T	*tail;

};

#endif
