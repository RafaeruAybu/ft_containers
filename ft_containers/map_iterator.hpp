#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "node.hpp"
#include "iterator_traits.hpp"

namespace ft {
    template <class T1, class T2, class Iter>
    class map_iterator
    {
    public:
        typedef Iter iterator_type;
        typedef ft::bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference reference;

    private:
        typedef Node<T1, T2>* nodePointer;
        typedef Node<T1, T2> rep;
        nodePointer ptr;

    public:
        map_iterator(nodePointer ptr = 0)
        : ptr(ptr)
        {}

        template<class U>
        map_iterator(const map_iterator<T1, T2, U>& other) :ptr(other.base())
        {}

        map_iterator& operator=(const map_iterator& other)
        {
            if (this == &other)
                return *this;
            ptr = other.ptr;
            return *this;
        }

        ~map_iterator()
        {}

        nodePointer base() const
        {
            return ptr;
        }

        bool operator==(const map_iterator& other) const
        {
            return ptr == other.base();
        }

        bool operator!=(const map_iterator& other) const
        {
            return ptr != other.base();
        }

        reference operator*() const
        {
            return *(ptr->data);
        }

        pointer operator->() const
        {
            return ptr->data;
        }

        map_iterator& operator++()
        {
            ptr = next(ptr);
            return *this;
        }

        map_iterator operator++(int)
        {
            map_iterator tmp(*this);
            ptr = next(ptr);
            return tmp;
        }

        map_iterator& operator--()
        {
            ptr = prev(ptr);
            return *this;
        }

        map_iterator operator--(int)
        {
            map_iterator tmp(*this);
            ptr = prev(ptr);
            return tmp;
        }

    private:
        nodePointer maximum(nodePointer node)
        {
            while (node->right->type != rep::nil)
            {
                node = node->right;
            }
            return node;
        }

        nodePointer minimum(nodePointer node)
        {
            while (node->left->type != rep::nil)
            {
                node = node->left;
            }
            return node;
        }

        nodePointer next(nodePointer node)
        {
            if (node->type == rep::nil)
                return node;
            if (node->right->type != rep::nil)
                return minimum(node->right);
            nodePointer ptr = node->parent;
            while (ptr->type != rep::nil && node == ptr->right)
            {
                node = ptr;
                ptr = ptr->parent;
            }
            return ptr;
        }

        nodePointer prev(nodePointer node)
        {
            if (node->type == rep::nil)
                return node->parent;
            if (node->type != rep::nil && node->left->type != rep::nil)
                return maximum(node->left);
            nodePointer ptr = node->parent;
            while (ptr->type != rep::nil && node == ptr->left)
            {
                node = ptr;
                ptr = ptr->parent;
            }
            return ptr->type != rep::nil ? ptr : node;
        }
    }; //map_iterator

} //namespace ft

#endif
