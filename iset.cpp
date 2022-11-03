#include "iset.h"

Node* create_node(const int& key = 0) {
	Node* n = new Node;
	n->_key = key;
	n->_degree = 0;
	return n;
}

void  delete_node(Node* node) {
	if (node == nullptr) return;

	node->_left_child    = nullptr;
	node->_right_child   = nullptr;
	node->_right_brother = nullptr;
	node->_parent        = nullptr;
	delete node;
}

Node*  link_trees(Node* r1, Node* r2) {
	if ((r1 == nullptr) || (r2 == nullptr)) return;

	if (r1->_key < r2->_key) {
		++r1->_degree;
		Node* ex_rc = r1->_right_child;

		r1->_right_child = r2;
		r2->_parent      = r1;
		
		if (ex_rc != nullptr)
			ex_rc->_right_brother = r2;

		return r1;
	}
	else {
		++r2->_degree;
		Node* ex_rc = r2->_right_child;

		r2->_right_child = r1;
		r1->_parent = r2;

		if (ex_rc != nullptr)
			ex_rc->_right_brother = r1;

		return r2;
	}
}

Node*  insert(Node* root_list, const int& key) {
	if (root_list != nullptr) {
		Node* n = create_node(key);
		n->_right_brother = root_list;
		root_list = n;
		root_list = heapify(root_list);
	}
	else {
		Node* n = create_node(key);
		root_list = n;
	}

	return root_list;
}

Node*  heapify(Node* root_list) {
	if (root_list != nullptr) {
		Node* iter1 = root_list;
		Node* iter2 = nullptr;

		while (iter1->_right_brother != nullptr) {
			iter1 = iter1->_right_brother;
		}

		Node* tail = iter1;
		Node* nn   = nullptr;
		iter1      = root_list;

		while (iter1->_right_brother != nullptr) {
			iter2 = iter1;
			iter1 = iter1->_right_brother;

			if (iter1->_degree == iter2->_degree) {
				nn = link_trees(iter1, iter2);
				tail->_right_brother = nn;
				root_list = tail;
				tail = tail->_right_brother;
			}
		}

		return root_list;
	}
	else return root_list;
}

void clear_heap(Node* root_list) {
	if (root_list == nullptr) return;

	Node* iter1 = root_list;
	Node* iter2 = nullptr;

	while (iter1->_right_brother != nullptr) {
		iter2 = iter1;
		iter1 = iter1->_right_brother;
		recursive_clear(iter2);
	}

	recursive_clear(iter1);
}

void recursive_clear(Node* node) {
	if (node == nullptr) return;
	if (node->_degree == 0) delete_node(node);
	else {
		Node* iter1 = node->_left_child;
		Node* iter2 = nullptr;

		for (int i = 0; i < node->_degree; ++i) {
			iter2 = iter1;
			iter1 = iter1->_right_brother;
			recursive_clear(iter2);
		}

		recursive_clear(iter1);
	}
}

int   get_min(Node* root_list) {
	if (root_list == nullptr) throw;

	Node* iter = root_list;
	int   min  = iter->_key;

	while (iter->_right_brother != nullptr) {
		iter = iter->_right_brother;
		if (min > iter->_key) min = iter->_key;
	}

	return min;
}

int   delete_min(Node* root_list) {
	if (root_list == nullptr) throw;

	Node* prev     = root_list;
	Node* cur      = root_list;
	Node* mnd_prev = nullptr;
	Node* min_node = root_list;

	while (cur->_right_brother != nullptr) {
		prev = cur;
		cur = cur->_right_brother;
		if (min_node->_key > cur->_key) {
			mnd_prev = prev;
			min_node = cur;
		}
	}

	mnd_prev->_right_brother = min_node->_right_brother;


	return min_node->_key;
}

// метод grow, чтобы дети взрослели и помещались в корневой список
// метод insert для вставки узла в конец