#include <iostream>
#include "iset.h"

int main() {
	vector<int> vec{9, 8, 7, 6, 5, 4, 3, 2, 1};
	Node* heap = create_heap(vec);
	clear_heap(heap);
	return EXIT_SUCCESS;
}