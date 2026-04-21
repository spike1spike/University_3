#include <iostream>
#include <random>
#include <chrono>

#include "Sorting.h"	

// Вспомогательные функции
std::vector<int> generate_array(int array_size, int element_min_value, int element_max_value) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution dist(element_min_value, element_max_value);

	std::vector<int> array;
	for (int i = 0; i < array_size; i++) {
		array.push_back(dist(gen));
	}

	return array;
}

// Проверка сортировки массивов
void print_array(std::vector<int>& array) {
	for (int i = 0; i < array.size() - 1; i++) {
		std::cout << array[i] << ",";
	}
	std::cout << array[array.size() - 1] << std::endl;
}

void test_array_sort(int array_size, int element_min_value, int element_max_value) {
	std::vector<int> array = generate_array(array_size, element_min_value, element_max_value);
	std::vector<int> sorted_array;

	std::cout << "Исходный массив:" << std::endl;
	print_array(array);
	std::cout << std::endl;

	sorted_array = array;
	shell_sort(sorted_array);
	std::cout << "Сортировка Шелла:" << std::endl;
	print_array(sorted_array);
	std::cout << std::endl;

	sorted_array = array;
	radix_sort(sorted_array);
	std::cout << "Поразрядная сортировка:" << std::endl;
	print_array(sorted_array);
	std::cout << std::endl;

	sorted_array = array;
	quick_sort(sorted_array, 0, sorted_array.size() - 1);
	std::cout << "Быстрая сортировка:" << std::endl;
	print_array(sorted_array);
	std::cout << std::endl;
}

// Измерение времени выполнения
template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
	auto start_time = std::chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	auto end_time = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	double duration_seconds = duration.count() / 1000.0;

	return duration_seconds;
}

void measure_sorting_time_all(int array_max_size, int array_step, int element_min_value, int element_max_value) {
	std::vector<std::vector<int>> big_array;
	for (int i = array_step; i <= array_max_size; i += array_step) {
		big_array.push_back(generate_array(i, element_min_value, element_max_value));
	}

	std::cout << "Сортировка Шелла" << "\n\n";
	for (int i = 0; i < big_array.size(); i++) {
		std::vector<int> array = big_array[i];
		auto execution_time = measure_execution_time(shell_sort, array);
		std::cout << "Размер массива: " << array.size() << " ; Время: " << execution_time << " сек" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Поразрядная сортировка" << "\n\n";
	for (int i = 0; i < big_array.size(); i++) {
		std::vector<int> array = big_array[i];
		auto execution_time = measure_execution_time(radix_sort, array);
		std::cout << "Размер массива: " << array.size() << " ; Время: " << execution_time << " сек" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Быстрая сортировка" << "\n\n";
	for (int i = 0; i < big_array.size(); i++) {
		std::vector<int> array = big_array[i];
		auto execution_time = measure_execution_time(quick_sort, array, 0, array.size() - 1);
		std::cout << "Размер массива: " << array.size() << " ; Время: " << execution_time << " сек" << std::endl;
	}
}


int main() {
	setlocale(LC_CTYPE, "rus");

	int array_size = 1000000;
	int array_step = 100000;
	int element_min_value = 0;
	int element_max_value = 1000000;

	//test_array_sort(array_size, element_min_value, element_max_value);

	measure_sorting_time_all(array_size, array_step, element_min_value, element_max_value);

	return 0;
}