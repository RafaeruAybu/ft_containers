#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"

namespace ft {

template<class T1, class T2, class Compare, class Alloc>
class tree {
public:
    typedef T1 key_type;
    typedef T2 mapped_type;
    typedef Compare key_compare;
    typedef typename Alloc::template rebind< Node<T1, T2> >::other allocator_type;
    typedef typename allocator_type::value_type value_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

private:
    allocator_type alloc;
    key_compare cmp;
    pointer head;
    pointer m_nil;
    size_type m_size;
    typedef Node<T1, T2> rep;

public:
    tree() : alloc(), cmp(key_compare()), head(alloc.allocate(1)), m_nil(head), m_size(0)
    {
        alloc.construct(m_nil, value_type(key_type(), mapped_type(), NULL, rep::nil));
    }

    ~tree()
    {
        clear(head);
        free_node(m_nil);
    }

    tree& operator=(const tree& other)
    {
        if (this == &other)
            return *this;
        clear();
        cmp = other.cmp;
        for (pointer ptr = other.begin(); ptr != other.end(); ptr = next(ptr)) {
            insert(*ptr->data);
        }
        return *this;
    }

    pointer begin()
    {
        return minimum(head);
    }

    pointer begin() const
    {
        return minimum(head);
    }

    pointer end()
    {
        return m_nil;
    }

    pointer end() const
    {
        return m_nil;
    }

    size_type size() const
    {
        return m_size;
    }

    size_type max_size() const
    {
        return alloc.max_size();
    }

    void clear()
    {
        clear(head);
    }

    ft::pair<pointer, bool> insert(ft::pair<key_type, mapped_type> pair)
    {
        pointer current, parent, new_node;

        for (current = head, parent = m_nil; current != m_nil;) {
            if (pair.first == current->data->first)
                return ft::pair<pointer, bool>(current, false);
            parent = current;
            current = cmp(pair.first, current->data->first) ? current->left : current->right;
        }
        new_node = alloc.allocate(1);
        alloc.construct(new_node, value_type(pair.first, pair.second, m_nil, rep::red));
        new_node->parent = parent;
        if (parent == m_nil)
            head = new_node;
        else {
            if (cmp(pair.first, parent->data->first))
                parent->left = new_node;
            else
                parent->right = new_node;
        }
        insert_fixup(new_node);
        m_nil->parent = maximum(head);
        ++m_size;
        return ft::pair<pointer, bool>(new_node, true);
    }

    bool erase(key_type key)
    {
        pointer node = find(head, key);
        if (node == m_nil)
            return false;
        erase_node(node);
        --m_size;
        return true;
    }

    void swap(tree& other)
    {
        std::swap(m_nil, other.m_nil);
        std::swap(head, other.head);
        std::swap(cmp, other.cmp);
        std::swap(alloc, other.alloc);
        std::swap(m_size, other.m_size);
    }

    pointer find(key_type key) const
    {
        return find(head, key);
    }

    pointer lower_bound(const key_type key) const
    {
        pointer	node = head;
        pointer	ret = m_nil;

        while (node != m_nil)
        {
            if (!cmp(node->data->first, key))
            {
                ret = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        return ret;
    }

    pointer upper_bound(const key_type key) const
    {
        pointer	node = head;
        pointer	ret = m_nil;

        while (node != m_nil)
        {
            if (cmp(key, node->data->first))
            {
                ret = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        return ret;
    }

private:
    pointer find(pointer node, key_type key) const
    {
        if (node != m_nil)
        {
            if (node->data->first == key)
                return node;
            else if (cmp(key, node->data->first))
                return find(node->left, key);
            else
                return find(node->right, key);
        }
        return m_nil;
    }

    pointer maximum(pointer node) const
    {
        for (; node->type != rep::nil && node->right->type != rep::nil; node = node->right) { }
        return node;
    }

    pointer minimum(pointer node) const
    {
        for (; node->type != rep::nil && node->left->type != rep::nil; node = node->left) { }
        return node;
    }

    pointer next(pointer node)
    {
        if (node->type == rep::nil)
            return node;
        if (node->right->type != rep::nil)
            return minimum(node->right);
        pointer tmp = node->parent;
        for (; tmp->type != rep::nil && node == tmp->right; node = tmp, tmp = tmp->parent) { }
        return tmp;
    }

    pointer prev(pointer node)
    {
        if (node->type == rep::nil)
            return node->parent;
        if (node->type != rep::nil && node->left->type != rep::nil)
            return maximum(node->left);
        pointer tmp = node->parent;
        for (; tmp->type != rep::nil && node == tmp->left; node = tmp, tmp = tmp->parent) { }
        return tmp->type != rep::nil ? tmp : node;
    }

    void free_node(const pointer& node)
    {
        alloc.destroy(node);
        alloc.deallocate(node, 1);
    }

    void clear(pointer& node)
    {
        if (node == NULL || node == m_nil)
            return;

        clear(node->left);
        clear(node->right);
        if (node == head) {
            free_node(head);
            head = m_nil;
            m_nil->parent = NULL;
            m_size = 0;
        }
        else
            free_node(node);
    }

    void erase_node(pointer z)
    {
        pointer x, y;

        if (z != m_nil) {
            if (z->left == m_nil || z->right == m_nil)
                y = z;
            else {
                y = z->right;
                for (; y->left != m_nil; y = y->left) { }
            }
            if (y->left != m_nil)
                x = y->left;
            else
                x = y->right;
            if (x != m_nil)
                x->parent = y->parent;
            if (y->parent == m_nil)
                head = x;
            else {
                if (y == y->parent->left)
                    y->parent->left = x;
                else
                    y->parent->right = x;
            }
            if (y != z) {
                delete z->data;
                z->data = new ft::pair<const key_type, mapped_type>(y->data->first, y->data->second);
            }
            if (y->type == rep::black)
                delete_fixup(x);
            alloc.destroy(y);
            alloc.deallocate(y, 1);
            m_nil->parent = maximum(head);
        }
    }

    void insert_fixup(pointer x)
    {
        for (; x != head && x->parent->type == rep::red;) {
            if (x->parent == x->parent->parent->left) {
                pointer y = x->parent->parent->right;
                if (y->type == rep::red) {
                    x->parent->type = rep::black;
                    y->type = rep::black;
                    x->parent->parent->type = rep::red;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->right) {
                        x = x->parent;
                        rotate_left(x);
                    }
                    x->parent->type = rep::black;
                    x->parent->parent->type = rep::red;
                    rotate_right(x->parent->parent);
                }
            } else {
                pointer y = x->parent->parent->left;
                if (y->type == rep::red) {
                    x->parent->type = rep::black;
                    y->type = rep::black;
                    x->parent->parent->type = rep::red;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        rotate_right(x);
                    }
                    x->parent->type = rep::black;
                    x->parent->parent->type = rep::red;
                    rotate_left(x->parent->parent);
                }
            }
        }
        head->type = rep::black;
    }

    void delete_fixup(pointer x)
    {
        for (; x != head && x->type == rep::black;) {
            if (x == x->parent->left) {
                pointer w = x->parent->right;
                if (w->type == rep::red) {
                    w->type = rep::black;
                    x->parent->type = rep::red;
                    rotate_left(x->parent);
                    w = x->parent->right;
                }
                if (w->left->type == rep::black && w->right->type == rep::black) {
                    w->type = rep::red;
                    x = x->parent;
                } else {
                    if (w->right->type == rep::black) {
                        w->left->type = rep::black;
                        w->type = rep::red;
                        rotate_right(w);
                        w = x->parent->right;
                    }
                    w->type = x->parent->type;
                    x->parent->type = rep::black;
                    w->right->type = rep::black;
                    rotate_left(x->parent);
                    x = head;
                }
            } else {
                pointer w = x->parent->left;
                if (w->type == rep::red) {
                    w->type = rep::black;
                    x->parent->type = rep::red;
                    rotate_right(x->parent);
                    w = x->parent->left;
                }
                if (w->right->type == rep::black && w->left->type == rep::black) {
                    w->type = rep::red;
                    x = x->parent;
                } else {
                    if (w->left->type == rep::black) {
                        w->right->type = rep::black;
                        w->type = rep::red;
                        rotate_left(w);
                        w = x->parent->left;
                    }
                    w->type = x->parent->type;
                    x->parent->type = rep::black;
                    w->left->type = rep::black;
                    rotate_right(x->parent);
                    x = head;
                }
            }
        }
        if (x->type != rep::nil)
            x->type = rep::black;
    }

    void rotate_left(pointer x)
    {
        pointer y = x->right;
        x->right = y->left;
        if (y->left != m_nil)
            y->left->parent = x;
        if (y != m_nil)
            y->parent = x->parent;
        if (x->parent == m_nil)
            head = y;
        else {
            if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        y->left = x;
        if (x != m_nil)
            x->parent = y;
    }

    void rotate_right(pointer x)
    {
        pointer y = x->left;
        x->left = y->right;
        if (y->right != m_nil)
            y->right->parent = x;
        if (y != m_nil)
            y->parent = x->parent;
        if (x->parent == m_nil)
            head = y;
        else {
            if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
        }
        y->right = x;
        if (x != m_nil)
            x->parent = y;
    }
}; //Tree

} //namespace ft

#endif
