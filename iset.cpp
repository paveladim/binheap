#include "iset.h"

Node* create_node(const int& key) {
	Node* n = new Node;
	n->_key = key;
	n->_degree = 0;
	n->_parent = nullptr;
	n->_right_brother = nullptr;
	n->_left_child = nullptr;
	n->_right_child = nullptr;
	return n;
}

void  delete_node(Node* node) {
	if (node == nullptr) return;

	node->_left_child = nullptr;
	node->_right_child = nullptr;
	node->_right_brother = nullptr;
	node->_parent = nullptr;
	delete node;
}

Node* link_trees(Node* r1, Node* r2) {
	if ((r1 == nullptr) && (r2 == nullptr)) return nullptr;
	if ((r1 != nullptr) && (r2 == nullptr)) return r1;
	if ((r1 == nullptr) && (r2 != nullptr)) return r2;

	if (r1->_degree != r2->_degree) throw;

	if (r1->_key < r2->_key) {
		++(r1->_degree);
		Node* ex_lc = r1->_left_child;

		r1->_left_child = r2;
		if (r1->_right_brother == r2) r1->_right_brother = nullptr;
		r2->_parent = r1;

		r2->_right_brother = ex_lc;

		Node* iter = r1->_left_child;
		while (iter->_right_brother != nullptr)
			iter = iter->_right_brother;

		r1->_right_child = iter;

		return r1;
	}
	else {
		++(r2->_degree);
		Node* ex_lc = r2->_left_child;

		r2->_left_child = r1;
		if (r2->_right_brother == r1) r2->_right_brother = nullptr;
		r1->_parent = r2;

		r1->_right_brother = ex_lc;

		Node* iter = r2->_left_child;
		while (iter->_right_brother != nullptr)
			iter = iter->_right_brother;

		r2->_right_child = iter;

		return r2;
	}
}

Node* insert(Node* root_list, const int& key) {
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
	else if ((rl1 == nullptr) && (rl2 != nullptr)) {
		root_list = rl2;
	}
	else {
		vector<Node*> merged(1000, nullptr);
		Node* iter1 = rl1;
		Node* iter2 = rl2;
		Node* chng1 = nullptr;
		Node* chng2 = nullptr;
		Node* temp = nullptr;

		while (iter1 != nullptr) {
			chng1 = iter1->_right_brother;
			add_to_merged(merged, iter1);
			iter1 = chng1;
		}

		while (iter2 != nullptr) {
			chng2 = iter2->_right_brother;
			add_to_merged(merged, iter2);
			iter2 = chng2;
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

Node* order_trees(Node* src) {
	Node* iter = src;
	Node* chng = nullptr;
	Node* root_list = nullptr;
	vector<Node*> merged(1000, nullptr);

	while (iter != nullptr) {
		chng = iter->_right_brother;
		add_to_merged(merged, iter);
		iter = chng;
	}

	for (size_t i = 0; i < merged.size(); ++i) {
		if ((root_list == nullptr) && (merged[i] != nullptr)) {
			root_list = merged[i];
			iter = root_list;
		}
		else if (merged[i] != nullptr) {
			iter->_right_brother = merged[i];
			iter = iter->_right_brother;
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
	int   min = iter->_key;

	while (iter->_right_brother != nullptr) {
		iter = iter->_right_brother;
		if (min > iter->_key) min = iter->_key;
	}

	return min;
}

int   delete_min(Node** root_list) {
	if (*root_list == nullptr) throw;

	Node* prev = nullptr;
	Node* cur = *root_list;
	Node* min_prev = nullptr;
	Node* min_node = *root_list;
	int key = 0;

	while (cur->_right_brother != nullptr) {
		prev = cur;
		cur = cur->_right_brother;
		if (min_node->_key > cur->_key) {
			min_prev = prev;
			min_node = cur;
		}
	}

	if ((min_node == *root_list) && (min_node->_right_brother == nullptr)) {
		Node* to_attach = min_node->_left_child;
		grow(to_attach);
		to_attach = order_trees(to_attach);
		key = min_node->_key;
		delete_node(min_node);
		*root_list = to_attach;
	}
	else if ((min_node == *root_list) && (min_node->_right_brother != nullptr)) {
		Node* to_attach = min_node->_left_child;
		grow(to_attach);
		to_attach = order_trees(to_attach);
		*root_list = (*root_list)->_right_brother;
		key = min_node->_key;
		delete_node(min_node);
		*root_list = merge(*root_list, to_attach);
	}
	else {
		min_prev->_right_brother = min_node->_right_brother;
		grow(min_node->_left_child);
		Node* to_attach = order_trees(min_node->_left_child);
		*root_list = merge(*root_list, to_attach);
		key = min_node->_key;
		delete_node(min_node);
	}

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
		node->_right_brother = nullptr;
		merged[node->_degree] = node;
	}
	else {
		Node* nd = merged[node->_degree];
		merged[node->_degree] = nullptr;
		node = link_trees(node, nd);
		add_to_merged(merged, node);
	}
}

Node* create_heap(const vector<int> src) {
	Node* root_list = nullptr;
	for (auto& elem : src)
		root_list = insert(root_list, elem);

	return root_list;
}

void emersion(Node** root_list, Node* src) {
	if (src == nullptr) return;
	Node* iter = src;
	while ((iter->_parent != nullptr) && (iter->_key < iter->_parent->_key)) {
		int tmp = iter->_key;
		iter->_key = iter->_parent->_key;
		iter->_parent->_key = tmp;

		iter = iter->_parent;
	}
}

void decrease_key(Node** root_list, Node* src, int delta) {
	if (src == nullptr) return;
	src->_key -= min(delta, numeric_limits<int>::max() - src->_key);
	emersion(root_list, src);
}

void delete_inner(Node** root_list, Node* src) {
	decrease_key(root_list, src, numeric_limits<int>::max());
	delete_min(root_list);
}

int partition(int* arr, int lo, int hi, int idx) {
	swap(arr[idx], arr[hi - 1]);
	int x = arr[hi - 1];
	int i = lo - 1;

	for (int j = lo; j < hi; ++j)
		if (arr[j] < x) {
			++i;
			swap(arr[j], arr[i]);
		}

	swap(arr[hi - 1], arr[i + 1]);
	return i + 1;
}

int find_median(vector<int>& src, int lo, int hi) {
	if ((hi - lo) % 2 == 0)
		return src[(hi + lo) / 2 - 1];
	else
		return src[(hi + lo) / 2];
}

void build_medians(vector<int>& src, int lo, int hi, vector<int>& meds) {
	vector<int> tmp(src.begin() + lo, src.begin() + hi);
	if (hi - lo < 6) {
		sort(tmp.begin(), tmp.end());
		meds.push_back(find_median(tmp, 0, tmp.size()));
		return;
	}

	for (int i = 0; i < tmp.size(); i += 5) {
		sort(tmp.begin() + i, tmp.begin() + i + min(5, hi - lo - i));
		meds.push_back(find_median(tmp, i, i + min(5, hi - lo - i)));
	}
}

int select(vector<int>& src, int lo, int hi, int order) {
	if (hi - lo == 1)
		return src[lo];

	vector<int> medians;
	build_medians(src, lo, hi, medians);
	int x = 0;

	if (medians.size() > 1)
		x = select(medians, 0, medians.size(), medians.size() / 2);
	else
		x = medians[0];

	int idx = 0;
	for (int i = lo; i < hi; ++i)
		if (src[i] == x) {
			idx = i;
			break;
		}

	idx = partition(&src[0], lo, hi, idx);

	if (order - 1 == idx - lo)
		return src[order - 1 + lo];
	if (order - 1 < idx - lo)
		return select(src, lo, idx, order);
	else
		return select(src, idx + 1, hi, order - idx + lo - 1);
}

int kth_stat(vector<int>& src, int order) {
	std::vector<int> tmp(src);
	return select(tmp, 0, src.size(), order);
}