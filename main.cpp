#include <iostream>
#include <random>
#include <chrono>
#include "iset.h"

using namespace std;

void random_test() {
	mt19937 _generator(chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> uniform(-32768, 32767);

	chrono::time_point<chrono::steady_clock> _start, _end;
	clock_t st;
	chrono::duration<double> elapsed;

	uniform_int_distribution<int> uniform_for_size(1, 10000);
	int sz = uniform_for_size(_generator);

	uniform_int_distribution<int> uniform_for_order(1, sz);
	int order = uniform_for_order(_generator);

	cout << "Task:" << endl;
	cout << "Vector length: " << sz << endl;
	cout << "Order: " << order << endl;
	cout << endl;

	int ans1 = 0;
	int ans2 = 0;
	int true_ans = 0;

	vector<int> vec(sz);
	for (auto& elem : vec)
		elem = uniform(_generator);

	Node* heap = create_heap(vec);
	_start = chrono::steady_clock::now();
	st = clock();

	for (int i = 0; i < order; ++i) {
		ans1 = delete_min(&heap);
	}

	_end = chrono::steady_clock::now();

	elapsed = _end - _start;
	cout << "Binomial heap: " << elapsed.count() << " sec " << (clock() - st) << " clocks " << endl;
	cout << "Answer: " << ans1 << endl;
	cout << endl;

	_start = chrono::steady_clock::now();
	st = clock();

	ans2 = kth_stat(vec, order);

	_end = chrono::steady_clock::now();

	elapsed = _end - _start;
	cout << "Kth order statistic: " << elapsed.count() << " sec " << (clock() - st) << " clocks " << endl;
	cout << "Answer: " << ans1 << endl;
	cout << endl;

	sort(vec.begin(), vec.end());
	true_ans = vec[order - 1];

	cout << "True answer: " << true_ans << endl;

	clear_heap(heap);
}

void fixed_size_test(const int& size, const int& order) {
	mt19937 _generator(chrono::high_resolution_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> uniform(-32768, 32767);

	chrono::time_point<chrono::steady_clock> _start, _end;
	clock_t st;
	chrono::duration<double> elapsed;

	vector<int> vec(size);
	for (auto& elem : vec)
		elem = uniform(_generator);

	cout << "Task:" << endl;
	cout << "Vector length: " << size << endl;
	cout << "Order: " << order << endl;
	cout << endl;

	int ans1 = 0;
	int ans2 = 0;
	int true_ans = 0;

	Node* heap = create_heap(vec);
	_start = chrono::steady_clock::now();
	st = clock();

	for (int i = 0; i < order; ++i) {
		ans1 = delete_min(&heap);
	}

	_end = chrono::steady_clock::now();

	elapsed = _end - _start;
	cout << "Binomial heap: " << elapsed.count() << " sec " << (clock() - st) << " clocks " << endl;
	cout << "Answer: " << ans1 << endl;
	cout << endl;

	_start = chrono::steady_clock::now();
	st = clock();

	ans2 = kth_stat(vec, order);

	_end = chrono::steady_clock::now();

	elapsed = _end - _start;
	cout << "Kth order statistic: " << elapsed.count() << " sec " << (clock() - st) << " clocks " << endl;
	cout << "Answer: " << ans1 << endl;
	cout << endl;

	sort(vec.begin(), vec.end());
	true_ans = vec[order - 1];

	cout << "True answer: " << true_ans << endl;

	clear_heap(heap);
}

int main() {
	fixed_size_test(10, 10);
	return EXIT_SUCCESS;
}