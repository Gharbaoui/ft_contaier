#ifndef STACK
#define STACK

#include "../FT_VECTOR/vector/vector.hpp"

namespace ft
{
template<
    class TC,
    class Cont = ft::vector<TC>
> class stack
{
	public:
		typedef	Cont							container_type;
		typedef	typename Cont::value_type		value_type;
		typedef	typename Cont::size_type		size_type;
		typedef	typename Cont::reference		reference;
		typedef	typename Cont::const_reference	const_reference;

		explicit stack(const Cont& cont = Cont()) : c(cont) {}
		~stack() {}
		stack& operator=( const stack& other )
		{
			if (this != &other)
			{
				c = other.c;
			}
			return *this;
		}
		
		reference top()
		{
			return c.back();
		}

		const_reference top() const
		{
			return c.back();
		}
		
		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		void push( const value_type& value )
		{
			c.push_back(value);
		}

		void pop()
		{
			c.pop_back();
		}

		template< class T, class Container >
		friend bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return lhs.c == rhs.c;
		}

		template< class T, class Container >
		friend bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return lhs.c != rhs.c;
		}

		template< class T, class Container >
		friend bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return lhs.c < rhs.c;
		}

		template< class T, class Container >
		friend bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return lhs.c <= rhs.c;
		}

		template< class T, class Container >
		friend bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return lhs.c > rhs.c;
		}

		template< class T, class Container >
		friend bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return lhs.c >= rhs.c;
		}
	protected:
		container_type c;
};

};


#endif
