#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include <memory>
#include <iostream>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename allocator_type::difference_type difference_type;
    typedef ft::vector_iterator<pointer> iterator;
    typedef ft::vector_iterator<const_pointer> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef typename allocator_type::size_type size_type;

private:
    allocator_type alloc;
    pointer array;
	size_type array_size;
	size_type m_capacity;

public:
	explicit vector(const allocator_type& alloc = allocator_type())
	: alloc(alloc), array(0), array_size(0), m_capacity(0) {}

	explicit vector(size_type n, const value_type& value = value_type(),
					const allocator_type& alloc = allocator_type())
	: alloc(alloc), array(0), array_size(0), m_capacity(0)
	{
		assign(n, value);
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type())
	: alloc(alloc), array(0), array_size(0), m_capacity(0)
	{
		assign(first, last);
	}

	vector(const vector& other)
	: alloc(other.alloc), array(0), array_size(0), m_capacity(0)
	{
		assign(other.begin(), other.end());
	}

	~vector()
	{
		clear();
		alloc.deallocate(array, m_capacity);
	}

	vector& operator= (const vector& x)
    {
		if (this == &x)
        {
			return *this;
		}
		clear();
		insert(begin(), x.begin(), x.end());
		return *this;
	}

	iterator begin()
    {
		return iterator(array);
	}

	const_iterator begin() const
    {
		return const_iterator(array);
	}

	iterator end()
    {
		return iterator(array + array_size);
	}

	const_iterator end() const
    {
		return const_iterator(array + array_size);
	}

	reverse_iterator rbegin()
    {
		return reverse_iterator(array + array_size);
	}

	const_reverse_iterator rbegin() const
    {
		return const_reverse_iterator(array + array_size);
	}

	reverse_iterator rend()
    {
		return reverse_iterator(array);
	}

	const_reverse_iterator rend() const
    {
		return const_reverse_iterator(array);
	}

	size_type size() const
    {
		return array_size;
	}

	size_type max_size() const
    {
		return alloc.max_size();
	}

	void resize (size_type n, value_type val = value_type())
    {
		if (array_size > n)
        {
			for (; array_size > n; --array_size)
				alloc.destroy(array + array_size - 1);
		}
		else
        {
			if (!m_capacity || n > 2 * m_capacity)
				reserve(n);
			else if (n > m_capacity)
				reserve(m_capacity * 2);
			for (; array_size < n; ++array_size)
				alloc.construct(array + array_size, val);
		}
	}

    size_type capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return (array_size == 0);
    }

	void reserve (size_type n)
    {
		if (n > m_capacity)
        {
			verify_size(n);
			pointer new_ptr;
			size_type new_cap = n;
			size_type new_size = 0;
			try {
				new_ptr = alloc.allocate(new_cap);
				for (; new_size < array_size; ++new_size)
					alloc.construct(new_ptr + new_size, *(array + new_size));
				for (size_type i = 0; i < array_size; ++i)
					alloc.destroy(array + i);
				replacement(new_ptr, new_size, new_cap);
			}
            catch (...)
            {
				clear(new_ptr, new_size, new_cap);
			}
		}
	}

    reference at (size_type n)
    {
        if (n < 0 || n >= array_size)
        {
			throw std::out_of_range("vector");
		}
		return *(array + n);
    }

    const_reference at (size_type n) const
    {
		if (n < 0 || n >= array_size) {
			throw std::out_of_range("vector");
		}
		return *(array + n);
    }

    reference operator[] (size_type n)
    {
        return *(array + n);
    }

    const_reference operator[] (size_type n) const
    {
        return *(array + n);
    }

	reference front()
    {
		return *array;
	}

	const_reference front() const
    {
		return *array;
	}

	reference back()
    {
		return *(array + array_size - 1);
	}

	const_reference back() const
    {
		return *(array + array_size - 1);
	}

	pointer data()
    {
		return array;
	}

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
				 typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
    {
		clear();
		reserve(ft::distance(first, last));
		insert(begin(), first, last);
	}

	void assign (size_type n, const value_type& val)
    {
		clear();
		reserve(n);
		insert(begin(), n, val);
	}

	void push_back(const value_type& value)
	{
		if (array_size == m_capacity)
			resize(array_size + 1, value);
		else
			alloc.construct(array + array_size++, value);
	}

	void pop_back()
	{
		--array_size;
		alloc.destroy(array + array_size);
	}

	iterator insert(iterator position, const value_type& value)
	{
		size_type pos = ft::distance(begin(), position);
		insert(position, 1, value);
		return iterator(array + pos);
	}

	void insert(iterator position, size_type n, const value_type& value)
	{
		size_type pos = ft::distance(begin(), position);
		size_type new_size = 0;
		size_type new_cap;
		pointer new_ptr;

		if (array_size + n > m_capacity)
        {
			new_cap = !m_capacity ? n : m_capacity * 2 < n + array_size ? array_size + n : m_capacity * 2;
			verify_size(new_cap);
			try {
				new_ptr = alloc.allocate(new_cap);
				for (; new_size < n; ++new_size)
					alloc.construct(new_ptr + pos + new_size, value);
				move(new_ptr, array, pos, new_size);
				move(new_ptr + pos + n, array + pos, ft::distance(position, end()), new_size);
				replacement(new_ptr, new_size, new_cap);
			}
            catch (...)
            {
				clear(new_ptr + pos, new_size, new_cap);
				throw;
			}
		}
        else
        {
			move_reverse(array + array_size - 1 + n, array + array_size - 1, ft::distance(position, end()));
			for (size_type i = 0; i < n; ++i, ++array_size)
				alloc.construct(array + pos + i, value);
		}
	}

	template<class InputIterator>
	void insert(iterator position,
			    InputIterator first,
			    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
    {
		size_type n = ft::distance(first, last);
		size_type pos = ft::distance(begin(), position);
		size_type new_size(0);
		size_type new_cap(0);
		pointer new_ptr(0);

		if (array_size + n > m_capacity)
        {
			new_cap = m_capacity == 0 ? n : m_capacity * 2 < array_size + n ? array_size + n : m_capacity * 2;
			verify_size(new_cap);
			try {
				new_ptr = alloc.allocate(new_cap);
				for (; new_size < n; ++new_size, ++first)
					alloc.construct(new_ptr + pos + new_size, *first);
				move(new_ptr, array, pos, new_size);
				move(new_ptr + pos + n, array + pos, end() - position, new_size);
				replacement(new_ptr, new_size, new_cap);
			}
            catch (...)
            {
				clear(new_ptr, new_size, new_cap);
				throw;
			}
		}
        else
        {
			move_reverse(array + array_size - 1 + n, array + array_size - 1, end() - position);
			for (size_type i = 0; i < n; ++i, ++array_size, ++first)
				alloc.construct(array + pos + i, *first);
		}
	}

	iterator erase(iterator position)
    {
		return erase(position, position + 1);
	}

	iterator erase(iterator first, iterator last)
	{
		size_type n = ft::distance(first, last);
		for (size_type i = 0; i < n; ++i) {
			alloc.destroy(first.base() + i);
		}
		for (size_type i = 0, remains = ft::distance(last, end()); i < remains; ++i) {
			*(first.base() + i) = *(last.base() + i);
		}
		array_size -= n;
		return first;
	}

	void swap(vector& other) {
		std::swap(alloc, other.alloc);
		std::swap(array, other.array);
		std::swap(array_size, other.array_size);
		std::swap(m_capacity, other.m_capacity);
	}

	void clear()
    {
		for (; array_size > 0; --array_size)
			alloc.destroy(array + array_size - 1);
	}

	allocator_type get_allocator() const
    {
		return alloc;
	}

private:
	void verify_size(size_type n)
    {
		if (n < 0 || n > max_size())
			throw std::length_error("vector");
	}

	void verify_range(size_type n) const
	{
		if (n < 0 || n > size())
			throw std::out_of_range("vector");
	}

	void replacement(pointer new_array, size_type new_size, size_type new_cap)
	{
		alloc.deallocate(array, m_capacity);
		array_size = new_size;
		m_capacity = new_cap;
		array = new_array;
	}

	void clear(pointer new_array, size_type new_size, size_type new_cap)
	{
		while (new_size > 0) {
			alloc.destroy(new_array + new_size - 1);
			new_size--;
		}
		alloc.deallocate(new_array, new_cap);
	}

	void move(pointer dst, pointer src, size_type n, size_type& new_size)
	{
		for (size_type i = 0; i < n; ++i, ++new_size)
			*(dst + i) = *(src + i);
	}

	void move_reverse(pointer dst, pointer src, size_type n)
	{
		for (size_type i = 0; i < n; ++i)
			*(dst - i) = *(src - i);
	}
}; //vector

template<class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
	typename vector<T, Alloc>::const_iterator it2 = rhs.begin();
	for (; it1 != lhs.end(); ++it1, ++it2)
		if (*it1 != *it2)
			return false;
	return true;
}

template<class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
	typename vector<T, Alloc>::const_iterator it2 = rhs.begin();

	for (; it1 != lhs.end(); ++it1, ++it2) {
		if (it2 == rhs.end() || *it2 < *it1)
			return false;
		else if (*it1 < *it2)
			return true;
	}
	return it2 != rhs.end();
}

template<class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return rhs < lhs;
}

template<class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return !(lhs < rhs);
}

template<class T, class Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
{
	x.swap(y);
}

} //namespace ft

#endif //VECTOR_HPP
