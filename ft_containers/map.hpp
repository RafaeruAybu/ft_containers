#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const Key, T> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef ft::map_iterator<Key, T, value_type*> iterator;
    typedef ft::map_iterator<Key, T, const value_type*> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;
        value_compare(key_compare c)
        :comp(c)
        {}

    public:
        bool operator()(const value_type& x, const value_type& y) const
        {
            return comp(x.first, y.first);
        }
    };

private:
    tree<Key, T, Compare, Allocator> tree;
    key_compare m_comp;
    allocator_type m_alloc;

public:
    explicit map(const Compare& comp = key_compare(),
                const Allocator& alloc = allocator_type())
    :
    tree(), m_comp(comp), m_alloc(alloc)
    {}

    template<class InputIterator>
    map(InputIterator first,
            InputIterator last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
    :
    tree(), m_comp(comp), m_alloc(alloc)
    {
        insert(first, last);
    }

    map(const map& other)
    {
        *this = other;
    }

    ~map()
    {}

    map& operator=(const map& other)
    {

        tree = other.
                tree;
        m_alloc = other.m_alloc;
        m_comp = other.m_comp;
        return *this;
    }

    allocator_type get_allocator() const
    {
        return m_alloc;
    }

    mapped_type& at(const Key& key)
    {
        iterator it = find(key);
        if (it==end())
        {
            throw std::out_of_range("map");
        }
        return it->second;
    }

    const mapped_type& at(const Key& key) const
    {
        iterator it = find(key);
        if (it==end())
        {
            throw std::out_of_range("map");
        }
        return it->second;
    }

    mapped_type& operator[](const key_type& key)
    {
        ft::pair<iterator, bool> res = insert(ft::pair<Key, mapped_type>(key,
                                                                         tree.find(key)->data->second));
        return res.first->second;
    }

    iterator begin()
    {
        return iterator(tree.begin());
    }

    const_iterator begin() const
    {
        return const_iterator(tree.begin());
    }

    iterator end()
    {
        return iterator(tree.end());
    }

    const_iterator end() const
    {
        return const_iterator(tree.end());
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(tree.end());
    }

    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(tree.end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(tree.begin());
    }

    const_reverse_iterator rend() const
    {
        return reverse_iterator(tree.begin());
    }

    bool empty() const
    {
        return
        tree.size() == 0;
    }

    size_type size() const
    {
        return
        tree.size();
    }

    size_type max_size() const
    {
        return
        tree.max_size();
    }

    void clear()
    {

        tree.clear();
    }

    ft::pair<iterator, bool> insert(const value_type& val)
    {
        return tree.insert(val);
    }

    iterator insert(iterator hint, const value_type& val)
    {
        (void) hint;
        return tree.insert(val).first;
    }

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        for (; first!=last; ++first)
        {
            tree.insert(value_type(first->first, first->second));
        }
    }

    void erase(iterator pos)
    {
        tree.erase(pos->first);
    }

    void erase(iterator first, iterator last)
    {
        for (; first!=last;)
        {
            Key key = first->first;
            ++first;

            tree.erase(key);
        }
    }

    size_type erase(const key_type& key)
    {
        return tree.erase(key) ? 1 : 0;
    }

    void swap(map& other)
    {
        tree.swap(other.
        tree);
        std::swap(m_alloc, other.m_alloc);
        std::swap(m_comp, other.m_comp);
    }

    size_type count(const key_type& key) const
    {
        return (tree.find(key) != tree.end()) ? 1 : 0;
    }

    iterator find(const key_type& key)
    {
        return iterator(tree.find(key));
    }

    const_iterator find(const key_type& key) const
    {
        return const_iterator(tree.find(key));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
    {
        return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
    }

    ft::pair<iterator, iterator> equal_range(const key_type& key)
    {
        return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
    }

    iterator lower_bound(const key_type& key)
    {
        return iterator(tree.lower_bound(key));
    }

    const_iterator lower_bound(const key_type& key) const
    {
        return const_iterator(tree.lower_bound(key));
    }

    iterator upper_bound(const key_type& key)
    {
        return iterator(tree.upper_bound(key));
    }

    const_iterator upper_bound(const key_type& key) const
    {
        return const_iterator(tree.upper_bound(key));
    }

    key_compare key_comp() const
    {
        return m_comp;
    }

    value_compare value_comp() const
    {
        return value_compare(Compare());
    }

    friend bool operator==(const map<Key, T, Compare, Allocator>& lhs,
                            const map<Key, T, Compare, Allocator>& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
                            const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs==rhs);
    }

    friend bool operator<(const map<Key, T, Compare, Allocator>& lhs,
                            const map<Key, T, Compare, Allocator>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
                            const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(rhs<lhs);
    }

    friend bool operator>(const map<Key, T, Compare, Allocator>& lhs,
                            const map<Key, T, Compare, Allocator>& rhs)
    {
        return rhs<lhs;
    }

    friend bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
                            const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs<rhs);
    }
}; //map

} //namespace ft

#endif //MAP_HPP
