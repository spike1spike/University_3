#include "Sorting.h"
#include "Support.h"

const std::vector<int> array_sizes = { 100000, 1000000, 2000000, 3000000, 4000000, 5000000, 10000000};
const std::vector<int> thread_amounts = { 2, 4, 8 };
const bool calculate_speedup = true;

int main() {
	test_quick_sort(array_sizes, thread_amounts, calculate_speedup);

	return 0;
}