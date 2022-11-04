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
		root_list = merge(root_list, n);
	}
	else {
		Node* n = create_node(key);
		root_list = n;
	}

	return root_list;
}

Node* merge(Node* rl1, Node* rl2) {
	Node* root_list = nullptr;

	if ((rl1 == nullptr) && (rl2 == nullptr))
		return root_list;
	else if ((rl1 != nullptr) && (rl2 == nullptr))
		root_list = rl1;
	else if ((rl1 == nullptr) && (rl2 != nullptr))
		root_list = rl2;
	else {
		vector<Node*> merged(1000, nullptr);
		Node* iter1 = rl1;
		Node* iter2 = rl2;
		Node* temp = nullptr;

		while ((iter1->_right_brother != nullptr) && (iter2->_right_brother != nullptr)) {
			if (iter1->_degree < iter2->_degree) {
				add_to_merged(merged, iter1);
				iter1 = iter1->_right_brother;
			}
			else if (iter1->_degree > iter2->_degree) {
				add_to_merged(merged, iter2);
				iter2 = iter2->_right_brother;
			}
			else {
				temp = link_trees(iter1, iter2);
				add_to_merged(merged, iter2);
				iter1 = iter1->_right_brother;
				iter2 = iter2->_right_brother;
			}
		}

		while (iter1->_right_brother != nullptr) {
			add_to_merged(merged, iter1);
			iter1 = iter1->_right_brother;
		}

		while (iter2->_right_brother != nullptr) {
			add_to_merged(merged, iter2);
			iter2 = iter2->_right_brother;
		}

		for (size_t i = 0; i < merged.size(); ++i) {
			if ((root_list == nullptr) && (merged[i] != nullptr)) {
				root_list = merged[i];
				iter1 = root_list;
			}
			else if (merged[i] != nullptr) {
				iter1->_right_brother = merged[i];
				iter1 = iter1->_right_brother;
			}
		}
	}

	return root_list;
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
	int key = 0;

	while (cur->_right_brother != nullptr) {
		prev = cur;
		cur = cur->_right_brother;
		if (min_node->_key > cur->_key) {
			mnd_prev = prev;
			min_node = cur;
		}
	}

	mnd_prev->_right_brother = min_node->_right_brother;
	grow(min_node->_left_child);
	root_list = merge(root_list, min_node->_left_child);
	key = min_node->_key;
	delete_node(min_node);

	return key;
}

void grow(Node* to_grow) {
	if (to_grow == nullptr) return;

	Node* iter = to_grow;
	iter->_parent = nullptr;
	while (iter->_right_brother != nullptr) {
		iter = iter->_right_brother;
		iter->_parent = nullptr;
	}
}

void  add_to_merged(vector<Node*>& merged, Node* node) {
	if (merged.size() - 1 < node->_degree)
		merged.resize(node->_degree + 2);

	if (merged[node->_degree] == nullptr) {
		merged[node->_degree] = node;
	}
	else {
		Node* nd = merged[node->_degree];
		merged[node->_degree] = nullptr;
		node = link_trees(node, nd);
		add_to_merged(merged, node);
	}
}