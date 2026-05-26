#include "Sorting.h"

int partition(std::vector<int>& array, int low, int high) {
	int pivot = array[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (array[j] <= pivot) {
			i++;
			std::swap(array[i], array[j]);
		}
	}
	std::swap(array[i + 1], array[high]);
	return (i + 1);
}

void quick_sort(std::vector<int>& array, int low, int high) {
	if (low < high) {
		int pivot_index = partition(array, low, high);
		quick_sort(array, low, pivot_index - 1);
		quick_sort(array, pivot_index + 1, high);
	}
}

void quick_sort_parallel(std::vector<int>& array, int low, int high, std::counting_semaphore<max_threads>& semaphore) {
	if (low < high) {
		int pivot_index = partition(array, low, high);

		bool semaphore_acquired = semaphore.try_acquire();
		bool use_parallel = (semaphore_acquired) &&
			((pivot_index - 1) - low + 1 >= min_parallel_arr_size) &&
			(high - (pivot_index + 1) + 1 >= min_parallel_arr_size);

		if (use_parallel) {
			std::thread t(quick_sort_parallel, std::ref(array), low, pivot_index - 1, std::ref(semaphore));
			quick_sort_parallel(array, pivot_index + 1, high, semaphore);
			t.join();
			semaphore.release();
		}
		else {
			if (semaphore_acquired) { semaphore.release(); }
			quick_sort(array, low, pivot_index - 1);
			quick_sort(array, pivot_index + 1, high);
		}
	}
}