#include <iostream>
#include "iset.h"

int main() {
	vector<int> vec{9, 8, 7, 6, 5, 4, 3, 1, 2};
	Node* heap = create_heap(vec);
	int min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	min = delete_min(&heap);
	clear_heap(heap);
	return EXIT_SUCCESS;
}