#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

namespace ft
{

template <class T1, class T2>
class Node
{
public:
    enum e_color
    {
        nil,
        black,
        red
    };

    typedef ft::pair<const T1, T2> value_type;
    e_color type;
    Node* parent;
    Node* left;
    Node* right;
    value_type* data;

    Node(T1 key, T2 value, Node* nil = NULL, e_color type = black)
    : type(type), parent(nil), left(nil), right(nil), data(new value_type(key, value))
    {}

    Node(const Node& other)
    {
        *this = other;
    }

    Node& operator=(const Node& other)
    {
        if (this == &other)
        {
            return *this;
        }
        type = other.type;
        parent = other.parent;
        left = other.left;
        right = other.right;
        data = new value_type (other.data->first, other.data->second);
        return *this;
    }

    ~Node()
    {
        if (data)
        {
            delete data;
            data = NULL;
        }
    }

}; //NODE

} //namespace ft

#endif //NODE_HPP
