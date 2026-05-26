#pragma once

#include <vector>
#include <utility>
#include <thread>
#include <semaphore>
#include <functional>

const int min_parallel_arr_size = 10000;
const int max_threads = 32;

int partition(std::vector<int>& array, int low, int high);
void quick_sort(std::vector<int>& array, int low, int high);
void quick_sort_parallel(std::vector<int>& array, int low, int high, std::counting_semaphore<max_threads>& semaphore);