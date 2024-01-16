#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "node.hpp"

namespace ft {

template <class T, class Iter>
class set_iterator
{
public:
    typedef Iter iterator_type;
    typedef ft::bidirectional_iterator_tag iterator_category;
    typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
    typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
    typedef typename ft::iterator_traits<iterator_type>::reference reference;

private:
    typedef Node<T, bool>* nodePointer;
    nodePointer ptr;
    typedef Node<T, bool> t_node;

public:
    set_iterator(nodePointer ptr = 0)
    : ptr(ptr)
    {}

    template<class U>
    set_iterator(const set_iterator<T, U>& other)
    : ptr(other.base())
    {}

    set_iterator& operator=(const set_iterator& other)
    {
        if (this == &other)
            return *this;
        ptr = other.ptr;
        return *this;
    }

    ~set_iterator()
    {}

    nodePointer base() const
    {
        return ptr;
    }

    bool operator==(const set_iterator& other) const
    {
        return ptr == other.base();
    }

    bool operator!=(const set_iterator& other) const
    {
        return ptr != other.base();
    }

    reference operator*() const
    {
        return ptr->data->first;
    }

    pointer operator->() const
    {
        return &ptr->data->first;
    }

    set_iterator& operator++()
    {
        ptr = next(ptr);
        return *this;
    }

    set_iterator operator++(int)
    {
        set_iterator tmp(*this);
        ptr = next(ptr);
        return tmp;
    }

    set_iterator& operator--()
    {
        ptr = prev(ptr);
        return *this;
    }

    set_iterator operator--(int)
    {
        set_iterator tmp(*this);
        ptr = prev(ptr);
        return tmp;
    }

private:
    nodePointer maximum(nodePointer node)
    {
        while (node->right->type != t_node::nil)
        {
            node = node->right;
        }
        return node;
    }

    nodePointer minimum(nodePointer node)
    {
        while (node->left->type != t_node::nil)
        {
            node = node->left;
        }
        return node;
    }

    nodePointer next(nodePointer node)
    {
        if (node->type == t_node::nil)
            return node;
        if (node->right->type != t_node::nil)
            return minimum(node->right);
        nodePointer ptr = node->parent;
        while (ptr->type != t_node::nil && node == ptr->right)
        {
            node = ptr;
            ptr = ptr->parent;
        }
        return ptr;
    }

    nodePointer prev(nodePointer node)
    {
        if (node->type == t_node::nil)
            return node->parent;
        if (node->type != t_node::nil && node->left->type != t_node::nil)
            return maximum(node->left);
        nodePointer ptr = node->parent;
        while (ptr->type != t_node::nil && node == ptr->left)
        {
            node = ptr;
            ptr = ptr->parent;
        }
        return ptr->type != t_node::nil ? ptr : node;
    }
}; //set_iterator

} //namespace ft

#endif //SET_ITERATOR_HPP
