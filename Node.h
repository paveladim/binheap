#ifndef NODE_H
#define NODE_H

struct Node {
	int   _key;
	Node* _parent;
	Node* _left_child;
	Node* _right_child;
	Node* _right_brother;
	int   _degree;															   // amount of children

    Node& operator=(const Node& src) {
        if (this == &src)
            return *this;

		_key = src._key;
		_parent = src._parent;
		_left_child = src._left_child;
		_right_child = src._right_child;
		_right_brother = src._right_brother;
		_degree = src._degree;

        return *this;
    }
};

#endif