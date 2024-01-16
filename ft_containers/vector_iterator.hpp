#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

template <typename Iterator>
class vector_iterator
{
public:
	typedef Iterator iterator_type;
	typedef typename ft::random_access_iterator_tag iterator_category;
	typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
	typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
	typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
	typedef typename ft::iterator_traits<iterator_type>::reference reference;

private:
	pointer ptr;

public:
	vector_iterator(pointer ptr = 0)
    : ptr(ptr)
    {}

	template<class U>
	vector_iterator(const vector_iterator<U>& other) : ptr(other.base())
    {}

	virtual ~vector_iterator()
    {}

	pointer base() const { return ptr; }

	vector_iterator& operator=(const vector_iterator& other)
	{
		if (this != &other)
			ptr = other.ptr;
		return *this;
	}

	vector_iterator& operator-=(difference_type n)
	{
		ptr -= n;
		return *this;
	}

	vector_iterator& operator+=(difference_type n)
	{
		ptr += n;
		return *this;
	}

	vector_iterator operator-(difference_type n) const
    {
		vector_iterator it(*this);
		movePtr(it.ptr, n, 0);
		return (it);
	}

	template <typename T>
	ptrdiff_t operator-(const vector_iterator<T>& it)
    {
        return this->base() - it.base();
    }

	vector_iterator operator+(difference_type n) const
    {
		vector_iterator it(*this);
		movePtr(it.ptr, n, 1);
		return (it);
	}

	vector_iterator& operator++()
	{
		ptr++;
		return *this;
	}

	vector_iterator& operator--()
	{
		ptr--;
		return *this;
	}

	vector_iterator operator++(int)
	{
		vector_iterator tmp(*this);
		ptr++;
		return tmp;
	}

	vector_iterator operator--(int)
	{
		vector_iterator tmp(*this);
		ptr--;
		return tmp;
	}

	reference operator*()
    {
        return *ptr;
    }

	pointer operator->()
    {
        return ptr;
    }

	reference operator[](difference_type n) const
    {
        return *(ptr + n);
    }

	template <typename T>
	bool operator==(const vector_iterator<T>& other) const
    {
        return ptr == other.base();
    }

	template <typename T>
	bool operator!=(const vector_iterator<T>& other) const
    {
        return ptr != other.base();
    }

	template <typename T>
	bool operator>(const vector_iterator<T>& other) const
    {
        return ptr > other.base();
    }

	template <typename T>
	bool operator<(const vector_iterator<T>& other) const
    {
        return ptr < other.base();
    }

	template <typename T>
	bool operator>=(const vector_iterator<T>& other) const
    {
        return ptr >= other.base();
    }

	template <typename T>
	bool operator<=(const vector_iterator<T>& other) const
    {
        return ptr <= other.base();
    }

private:
	void movePtr(pointer& val, long nb, bool sign) const
	{
		int mov;
		if (sign == 1)
			mov = nb > 0 ? mov = 1: mov = -1;
		else
			mov = nb > 0 ? mov = -1: mov = 1;
		if (nb < 0)
			nb *= -1;
		for (; nb > 0; --nb)
			val += mov;
	}
}; //vector_iterator

template <typename T>
vector_iterator<T> operator+(size_t n, const vector_iterator<T> &iter)
{
    return iter + n;
}

template <typename T>
ptrdiff_t operator-(const vector_iterator<T>& lhi, const vector_iterator<T>& rhi)
{
    return lhi.base() - rhi.base();
}

} //namespace ft

#endif
