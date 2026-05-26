#include "Support.h"
#include "Sorting.h"

const int array_min_value = -1000000;
const int array_max_value = 1000000;
const std::string divider = "     ";

std::vector<int> generate_array(int array_size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(array_min_value, array_max_value);

	std::vector<int> array(array_size);
	for (int& x : array) {
		x = dist(gen);
	}

	return array;
}

void check_sorted(std::vector<int>& array) {
	if (not std::is_sorted(array.begin(), array.end())) {
		throw std::runtime_error("Array is not sorted");
	}
}

void test_quick_sort(const std::vector<int>& array_sizes, const std::vector<int>& thread_amounts, const bool calculate_speedup) {

	// Заголовок таблицы
	std::cout << "Size" << divider << "Sequence" << divider;
	for (int thread_amount : thread_amounts) {
		std::cout << thread_amount << " threads" << divider;
	}
	if (calculate_speedup) {
		for (int thread_amount : thread_amounts) {
			std::cout << "Speedup " << thread_amount << divider;
		}
	}
	std::cout << std::endl;

	// Содержание таблицы
	for (int array_size : array_sizes) {
		std::cout << array_size << divider;
		std::vector<int> array_original = generate_array(array_size);
		std::vector<int> array_copy = array_original;

		double exec_time_normal = measure_execution_time(quick_sort, array_copy, 0, array_copy.size() - 1);
		check_sorted(array_copy);
		std::cout << exec_time_normal << divider;

		std::vector<double> exec_times_parallel(thread_amounts.size());
		for (int i = 0; i < thread_amounts.size(); i++) {
			array_copy = array_original;
			std::counting_semaphore<max_threads> semaphore(thread_amounts[i] - 1);
			exec_times_parallel[i] = measure_execution_time(quick_sort_parallel, array_copy, 0, array_copy.size() - 1, semaphore);
			check_sorted(array_copy);
			std::cout << exec_times_parallel[i] << divider;
		}

		if (calculate_speedup) {
			for (double exec_time_parallel : exec_times_parallel) {
				double speedup = exec_time_normal / exec_time_parallel;
				std::cout << speedup << divider;
			}
		}

		std::cout << std::endl;
	}
}