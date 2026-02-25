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
			double result = simpson_rule(function, -4, 4, 2);
			Assert::AreEqual(result, 16, 6, L"Значения совпали с точностью 6");
		}

		TEST_METHOD(TestMethod2)
		{
			double result = simpson_rule(function, -4, 4, 6);
			Assert::AreEqual(result, 16, 1, L"Значения совпали с точностью 1");
		}

		TEST_METHOD(TestMethod3)
		{
			double result = simpson_rule(function, -4, 4, 10);
			Assert::AreEqual(result, 16, 0.5, L"Значения совпали с точностью 0.5");
		}

		TEST_METHOD(TestMethod4)
		{
			double result = simpson_rule(function, -4, 4, 102);
			Assert::AreEqual(result, 16, 0.05, L"Значения совпали с точностью 0.05");
		}

		TEST_METHOD(TestMethod5)
		{
			double result = simpson_rule(function, -4, 4, 502);
			Assert::AreEqual(result, 16, 0.0002, L"Значения совпали с точностью 0.0002");
		}
	};
}
