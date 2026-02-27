#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/ConsoleApplication1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			double result_1 = simpson_rule(function_1, -4, 0, 2);
			double result_2 = simpson_rule(function_2, 0, 4, 2);
			double result = result_1 + result_2;
			Assert::AreEqual(16, result, 0.01, L"Значения совпали с точностью 0.01");
		}

		TEST_METHOD(TestMethod2)
		{
			double result_1 = simpson_rule(function_1, -4, 0, 4);
			double result_2 = simpson_rule(function_2, 0, 4, 4);
			double result = result_1 + result_2;
			Assert::AreEqual(16, result, 0.01, L"Значения совпали с точностью 0.01");
		}

		TEST_METHOD(TestMethod3)
		{
			double result_1 = simpson_rule(function_1, -4, 0, 6);
			double result_2 = simpson_rule(function_2, 0, 4, 6);
			double result = result_1 + result_2;
			Assert::AreEqual(16, result, 0.01, L"Значения совпали с точностью 0.01");
		}
	};
}
