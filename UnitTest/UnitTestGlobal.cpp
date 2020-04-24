#include "pch.h"
#include "CppUnitTest.h"
#include "../h/global.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGlobal
{
	TEST_CLASS(TestMyAtoi)
	{
	public:
		
		TEST_METHOD(AboveZero)
		{
			Assert::AreEqual(123,my_atoi("123"));
		}
		TEST_METHOD(Zero)
		{
			Assert::AreEqual(0, my_atoi("0"));
		}
		TEST_METHOD(text)
		{
			Assert::AreEqual(-1, my_atoi("abc"));
		}

	};
	TEST_CLASS(TestMyAtof)
	{
	public:

		TEST_METHOD(AboveZero)
		{
			Assert::AreEqual(123.3, my_atof("123.3"));
		}
		TEST_METHOD(Zero)
		{
			Assert::AreEqual(0.0, my_atof("0"));
		}
		TEST_METHOD(text)
		{
			Assert::AreEqual(-1.0, my_atof("abc"));
		}

	};
}
