#include <iostream>
#include <random>
#include <chrono>
#include "iset.h"

using namespace std;

int main() {
	mt19937 _generator(chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> uniform(-32768, 32767);

	vector<int> vec(1000);
	for (auto& elem : vec)
		elem = uniform(_generator);

	Node* heap = create_heap(vec);

	int ans = 0;
	int true_ans = 0;
	for (int i = 0; i < 999; ++i) {
		ans = delete_min(&heap);
	}

	sort(vec.begin(), vec.end());
	true_ans = vec[999];

	clear_heap(heap);

	return EXIT_SUCCESS;
}