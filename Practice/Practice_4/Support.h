#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <string>

std::vector<int> generate_array(int array_size);

template <typename Func, typename... Args>
auto measure_execution_time(Func&& func, Args&&... args) {
	auto start_time = std::chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	auto end_time = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	double duration_seconds = duration.count() / 1000000.0;

	return duration_seconds;
}

void test_quick_sort(const std::vector<int>& array_sizes, const std::vector<int>& thread_amounts, bool calculate_speedup);