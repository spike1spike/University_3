#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication3/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(MaxSum_Single)
		{
			std::vector<int> v = { 8 };
			int result = find_max_subarray(v, 0, v.size() - 1);

			Assert::AreEqual(8, result);
		}

		TEST_METHOD(MaxSum_Multiple_1)
		{
			std::vector<int> v = { -2, 1, -3, 4, -1, 2, 1, -5 };
			int result = find_max_subarray(v, 0, v.size() - 1);

			Assert::AreEqual(6, result);
		}

		TEST_METHOD(MaxSum_Multiple_2)
		{
			std::vector<int> v = { 1, -3, -17, 1000, -53, 32, 4, -9 };
			int result = find_max_subarray(v, 0, v.size() - 1);

			Assert::AreEqual(1000, result);
		}

		TEST_METHOD(MaxSum_Multiple_3)
		{
			std::vector<int> v = { -6, -27, -999, -3, -88, -45, -21, -15 };
			int result = find_max_subarray(v, 0, v.size() - 1);

			Assert::AreEqual(-3, result);
		}

		TEST_METHOD(MaxSum_Multiple_4)
		{
			std::vector<int> v = { 0, 0, -15, 0, 0, 0, -4, 0 };
			int result = find_max_subarray(v, 0, v.size() - 1);

			Assert::AreEqual(0, result);
		}
	};
}
