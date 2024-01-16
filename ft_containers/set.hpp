#ifndef SET_HPP
#define SET_HPP

#include "tree.hpp"
#include "set_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class Compare = std::less<Key>,
		class Allocator = std::allocator<Key> >
class set
{
public:
    typedef Key key_type;
    typedef key_type value_type;
    typedef Compare key_compare;
    typedef key_compare value_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef ft::set_iterator<Key, const value_type *> iterator;
    typedef ft::set_iterator<Key, const value_type *> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
    tree<Key, bool, Compare, Allocator> m_tree;
    key_compare m_key_compare;
    allocator_type m_alloc;

public:

    explicit set(const Compare &comp = Compare(),
                 const Allocator &a = Allocator())
    : m_tree(), m_key_compare(comp), m_alloc(a)
    {}

    template<class InputIterator>
    set(InputIterator first, InputIterator last,
        const Compare &comp = Compare(), const Allocator &a = Allocator())
    : m_tree(), m_key_compare(comp), m_alloc(a)
    {
        insert(first, last);
    }

    set(const set<Key, Compare, Allocator> &x)
    {
        *this = x;
    }

    ~set()
    {}

    set<Key, Compare, Allocator> &operator=
            (const set<Key, Compare, Allocator> &x)
    {
        if (this == &x)
            return *this;
        m_tree = x.m_tree;
        m_alloc = x.m_alloc;
        m_key_compare = x.m_key_compare;
        return *this;
    }

    allocator_type get_allocator() const
    {
        return m_alloc;
    }

    iterator begin()
    {
        return const_iterator(m_tree.begin());
    }

    const_iterator begin() const
    {
        return const_iterator(m_tree.begin());
    }

    iterator end()
    {
        return const_iterator(m_tree.end());
    }

    const_iterator end() const
    {
        return const_iterator(m_tree.end());
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(m_tree.end());
    }

    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(m_tree.end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(m_tree.begin());
    }

    const_reverse_iterator rend() const
    {
        return reverse_iterator(m_tree.begin());
    }

    bool empty() const
    {
        return m_tree.size() == 0;
    }

    size_type size() const
    {
        return m_tree.size();
    }

    size_type max_size() const
    {
        return m_tree.max_size();
    }

	pair<iterator,bool> insert(const value_type& x)
    {
        return m_tree.insert(ft::pair<const value_type, bool>(x, true));
    }

    iterator insert(iterator position, const value_type& x)
    {
        (void) position;
        return m_tree.insert(ft::pair<value_type, bool>(x, true)).first;
    }

    template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
    {
        for (; first != last; ++first)
        {
            m_tree.insert(ft::pair<value_type, bool>(*first, true));
        }
    }

    void erase(iterator position)
    {
        m_tree.erase(*position);
    }

	size_type erase(const key_type& x)
    {
        return m_tree.erase(x) ? 1 : 0;
    }

	void erase(iterator first, iterator last)
    {
        for (; first != last;)
        {
            Key key = *first;
            ++first;
            m_tree.erase(key);
        }
    }

    void swap(set<Key,Compare,Allocator>& other)
    {
        m_tree.swap(other.m_tree);
        std::swap(m_alloc, other.m_alloc);
        std::swap(m_key_compare, other.m_key_compare);
    }

    void clear()
    {
        m_tree.clear();
    }

	key_compare key_comp() const
    {
        return m_key_compare;
    }

	value_compare value_comp() const
    {
        return value_compare(Compare());
    }

    iterator find(const key_type& x) const
    {
        return iterator(m_tree.find(x));
    }

	size_type count(const key_type& x) const
    {
        return (const_iterator(m_tree.find(x)) != end()) ? 1 : 0;
    }

	iterator lower_bound(const key_type& x) const
    {
        return iterator(m_tree.lower_bound(x));
    }

	iterator upper_bound(const key_type& x) const
    {
        return iterator(m_tree.upper_bound(x));
    }

	pair<iterator,iterator> equal_range(const key_type& x) const
    {
        return ft::pair<iterator, iterator>(lower_bound(x), upper_bound(x));
    }
}; //set

template <class Key, class Compare, class Allocator>
bool operator==(const set<Key,Compare,Allocator>& x,
                const set<Key,Compare,Allocator>& y)
{
    return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Compare, class Allocator>
bool operator< (const set<Key,Compare,Allocator>& x,
                const set<Key,Compare,Allocator>& y)
{
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class Compare, class Allocator>
bool operator!=(const set<Key,Compare,Allocator>& x,
                const set<Key,Compare,Allocator>& y)
{
    return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator> (const set<Key,Compare,Allocator>& x,
                const set<Key,Compare,Allocator>& y)
{
    return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=(const set<Key,Compare,Allocator>& x,
                const set<Key,Compare,Allocator>& y)
{
    return !(x < y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const set<Key,Compare,Allocator>& x,
                const set<Key,Compare,Allocator>& y)
{
    return !(y < x);
}

template <class Key, class Compare, class Allocator>
void swap(set<Key,Compare,Allocator>& x,
          set<Key,Compare,Allocator>& y)
{
    x.swap(y);
}

} //namespace ft

#endif //SET_HPP
