#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template<class T, class Container = ft::vector<T> >
class stack
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef typename container_type::size_type size_type;

protected:
	container_type c;

public:

	explicit stack(const container_type& c = container_type())
    : c(c)
    {}

	stack(const stack& x)
    : c(x.c)
    {}

	~stack()
    {};

	value_type& top()
    {
		return c.back();
	}

	const value_type& top() const
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

	void push(const value_type& value)
    {
		c.push_back(value);
	}

	void pop()
    {
		c.pop_back();
	}

	friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
		return lhs.c == rhs.c;
	}

	friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
		return lhs.c != rhs.c;
	}

	friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
		return lhs.c < rhs.c;
	}

	friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
		return lhs.c > rhs.c;
	}

	friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
		return lhs.c <= rhs.c;
	}

	friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
		return lhs.c >= rhs.c;
	}
};

} //namespace ft

#endif //STACK_HPP
