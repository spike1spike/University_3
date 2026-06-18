#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication3/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(MaxMass_Zero)
		{
			int capacity = 5;
			std::vector<int> v_weight = {45, 75, 100};
			int result = get_max_mass(capacity, v_weight);

			Assert::AreEqual(0, result);
		}

		TEST_METHOD(MaxMass_Natural_1)
		{
			int capacity = 15;
			std::vector<int> v_weight = {3, 8, 1, 2, 5};
			int result = get_max_mass(capacity, v_weight);

			Assert::AreEqual(15, result);
		}

		TEST_METHOD(MaxMass_Natural_2)
		{
			int capacity = 19;
			std::vector<int> v_weight = { 10, 10, 7, 7, 4 };
			int result = get_max_mass(capacity, v_weight);

			Assert::AreEqual(18, result);
		}

		TEST_METHOD(MaxMass_Natural_3)
		{
			int capacity = 12;
			std::vector<int> v_weight = {6, 5, 3, 3, 3, 3};
			int result = get_max_mass(capacity, v_weight);

			Assert::AreEqual(12, result);
		}

		TEST_METHOD(MaxMass_Natural_4)
		{
			int capacity = 102;
			std::vector<int> v_weight = { 97, 50, 25, 18, 7 };
			int result = get_max_mass(capacity, v_weight);

			Assert::AreEqual(100, result);
		}
	};
}
