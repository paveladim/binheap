#ifndef NODE_H
#define NODE_H

struct Node {
	int   _key;
	Node* _parent;
	Node* _left_child;
	Node* _right_child;
	Node* _right_brother;
	int   _degree;															   // amount of children
};

#endif