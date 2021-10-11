#ifndef VECT_CLASS
#define VECT_CLASS


template <
	typename T,
	typename Allocator = std::allocator<T>
>
class	vector{
	// member types
	public:
		typedef T					value_type;
		typedef	size_t				size_type; // double check here
		typedef Allocator			allocator_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
	/// member functions
		vector();
		explicit vector(size_type count);
		vector(vector const &);
		explicit vector(const Allocator& alloc);
		explicit 		vector( size_type count,
                 		const T& value,
                 		const Allocator& alloc = Allocator());
		~vector();
		vector			&operator=(vector const &);
		void			assign(size_type count, const T& value);
		allocator_type	get_allocator() const;
		// element access
		T				&operator[](size_t i);
		T const			&operator[](size_t i) const;
		reference		at(size_type pos);
		const_reference at(size_type pos) const;
		reference		front();
		const_reference front() const;
		reference		back();
		const_reference back() const;
		T				*data();
		T	const		*data() const;
		// capacity
		bool empty() const;
		size_type		max_size() const;
		size_t			size() const;
		size_type		capacity() const;
		void			reserve(size_type new_cap);
		void			shrink_to_fit();
		//modifiers
		void			clear();
		void			push_back(const T&);
		void			pop_back();
		void			resize(size_type count, T value = T());
		// helpers
		void			range_destroy(int, int, int);
	private:
		T					*_arr;
		size_t				_size;
		size_t				_index;
		size_t				_capacity;
		size_t				_usr_cap;
		bool				_clear_worked; // should set to be false 
		// for all functions that change _capacity
		size_t				_max_size;
		allocator_type		mem_manager;
};

#endif
