#include "CppUnitTest.h"
#include "../ConsoleApplication1/Sorting.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		std::vector<int> array_empty = {};
		std::vector<int> array_zero = { 0 };
		std::vector<int> array_maxten = { 7, 7, 10, 10, 2, 5, 5, 7, 0, 6 };
		std::vector<int> array_maxonehundred = { 91, 11, 58, 11, 70, 9, 1, 26, 2, 21 };
		std::vector<int> array_maxonehundred_negative = { 11, 58, 68, 36, -59, 89, -79, 77, 25, -13 };

		template<typename SortFunc, typename... Args>
		void TestSort(std::vector<int>& array, SortFunc&& sort_func, Args&&... args) {
			std::vector<int> array_sorted = array;
			std::sort(array_sorted.begin(), array_sorted.end());

			std::vector<int> array_test = array;
			sort_func(array_test, std::forward<Args>(args)...);

			Assert::AreEqual(array.size(), array_test.size());
			for (int i = 0; i < array.size(); i++) {
				Assert::AreEqual(array_sorted[i], array_test[i]);
			}
		}
		
		// Сортировка Шелла
		TEST_METHOD(ShellSort_Array_Empty)
		{
			TestSort(array_empty, shell_sort);
		}

		TEST_METHOD(ShellSort_Array_Zero)
		{
			TestSort(array_zero, shell_sort);
		}

		TEST_METHOD(ShellSort_Array_MaxTen)
		{
			TestSort(array_maxten, shell_sort);
		}

		TEST_METHOD(ShellSort_Array_MaxOneHundred)
		{
			TestSort(array_maxonehundred, shell_sort);
		}

		TEST_METHOD(ShellSort_Array_MaxOneHundred_Negative)
		{
			TestSort(array_maxonehundred_negative, shell_sort);
		}


		// Поразрядная сортировка
		TEST_METHOD(RadixSort_Array_Empty)
		{
			TestSort(array_empty, radix_sort);
		}

		TEST_METHOD(RadixSort_Array_Zero)
		{
			TestSort(array_zero, radix_sort);
		}

		TEST_METHOD(RadixSort_Array_MaxTen)
		{
			TestSort(array_maxten, radix_sort);
		}

		TEST_METHOD(RadixSort_Array_MaxOneHundred)
		{
			TestSort(array_maxonehundred, radix_sort);
		}


		// Быстрая сортировка
		TEST_METHOD(QuickSort_Array_Empty)
		{
			TestSort(array_empty, quick_sort, 0, array_empty.size() - 1);
		}

		TEST_METHOD(QuickSort_Array_Zero)
		{
			TestSort(array_zero, quick_sort, 0, array_zero.size() - 1);
		}

		TEST_METHOD(QuickSort_Array_MaxTen)
		{
			TestSort(array_maxten, quick_sort, 0, array_maxten.size() - 1);
		}

		TEST_METHOD(QuickSort_Array_MaxOneHundred)
		{
			TestSort(array_maxonehundred, quick_sort, 0, array_maxonehundred.size() - 1);
		}

		TEST_METHOD(QuickSort_Array_MaxOneHundred_Negative)
		{
			TestSort(array_maxonehundred_negative, quick_sort, 0, array_maxonehundred_negative.size() - 1);
		}
	};
}
