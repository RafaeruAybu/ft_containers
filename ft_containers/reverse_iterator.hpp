#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template<class Iterator>
class reverse_iterator
{
public:
	typedef Iterator iterator_type;
	typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
	typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
	typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
	typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
	typedef typename ft::iterator_traits<iterator_type>::reference reference;

private:
	iterator_type m_base;

public:
	reverse_iterator()
    {}

	reverse_iterator(const Iterator& other) : m_base(other.base())
    {}

	reverse_iterator(const reverse_iterator& other) : m_base(other.base())
    {}

	template<class U>
	reverse_iterator(const reverse_iterator<U>& other) : m_base(other.base())
    {}

	virtual ~reverse_iterator()
    {}

	iterator_type base() const
    {
		return m_base;
	}

	reference operator*() const
    {
		iterator_type it(m_base);
		--it;
		return *it;
	}

	pointer operator->() const
    {
		return &(operator*());
	}

	reverse_iterator operator+(difference_type n) const
    {
		return reverse_iterator(m_base - n);
	}

	reverse_iterator operator-(difference_type n) const
    {
		return reverse_iterator(m_base + n);
	}

	reverse_iterator& operator++()
    {
		m_base--;
		return *this;
	}

	reverse_iterator& operator--()
    {
		m_base++;
		return *this;
	}

	reverse_iterator operator++(int)
    {
		reverse_iterator temp(*this);
		m_base--;
		return temp;
	}

	reverse_iterator operator--(int)
    {
		reverse_iterator temp(*this);
		m_base++;
		return temp;
	}

	reverse_iterator& operator+=(difference_type n)
    {
		m_base -= n;
		return *this;
	}

	reverse_iterator& operator-=(difference_type n)
    {
		m_base += n;
		return *this;
	}

	reference operator[](difference_type n) const
    {
		return (this->base()[-n-1]);
	}

	template <class U>
	bool operator==(const reverse_iterator<U>& other) const
    {
		return m_base == other.base();
	}

	template <class U>
	bool operator!=(const reverse_iterator<U>& other) const
    {
		return m_base != other.base();
	}

	template <class U>
	bool operator<(const reverse_iterator<U>& other) const
    {
		return m_base > other.base();
	}

	template <class U>
	bool operator<=(const reverse_iterator<U>& other) const
    {
		return m_base >= other.base();
	}

	template <class U>
	bool operator>(const reverse_iterator<U>& other) const
    {
		return m_base <  other.base();
	}

	template <class U>
	bool operator>=(const reverse_iterator<U>& other) const
    {
		return m_base <= other.base();
	}

	template <class U>
	difference_type operator-(const reverse_iterator<U>& other)
    {
		return other.base() - m_base;
	}

	friend reverse_iterator operator+(difference_type n, const reverse_iterator& other)
    {
		return other + n;
	}
}; //reverse_iterator

} //namespace ft


#endif //REVERSE_ITERATOR_HPP