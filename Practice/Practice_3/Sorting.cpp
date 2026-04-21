#include "Sorting.h"

// Сортировка Шелла
void shell_sort(std::vector<int>& array) {
	int n = array.size();
	int step = n / 2;

	while (step > 0) {
		for (int i = step; i < n; i++) {
			int temp = array[i];
			int j = i;
			while ((j >= step) && (array[j - step] > temp)) {
				array[j] = array[j - step];
				j -= step;
			}
			array[j] = temp;
		}
		step = step / 2;
	}
}

// Поразрядная сортировка
std::vector<int> combine_baskets(std::vector<std::vector<int>>& baskets) {
	std::vector<int> combined_array;
	for (int i = 0; i < baskets.size(); i++) {
		combined_array.insert(combined_array.end(), baskets[i].begin(), baskets[i].end());
	}
	return combined_array;
}

void sort_by_digit(std::vector<int>& array, int digit) {
	std::vector<std::vector<int>> baskets(10);
	for (int i = 0; i < array.size(); i++) {
		int basket_index = (array[i] / digit) % 10;
		baskets[basket_index].push_back(array[i]);
	}
	array = combine_baskets(baskets);
}

void radix_sort(std::vector<int>& array) {
	if (array.empty()) {
		return;
	}

	int max_num = array[0];
	for (int i = 1; i < array.size(); i++) {
		if (array[i] > max_num) {
			max_num = array[i];
		}
	}
	int digit = 1;
	while ((max_num / digit) > 0) {
		sort_by_digit(array, digit);
		digit *= 10;
	}
}

// Быстрая сортировка
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