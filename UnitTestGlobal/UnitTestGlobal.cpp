#include "pch.h"
#include "CppUnitTest.h"
#include "../h/global.h"
#include "../cpp/global.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTranslate
{
	TEST_CLASS(TestAtoi)
	{
	public:
		
		TEST_METHOD(Num)
		{
			Assert::AreEqual(123, my_atoi("123"));
		}
	};
	TEST_CLASS(TestAtof)
	{
	public:

		TEST_METHOD(Num)
		{
			Assert::AreEqual(123.3, my_atof("123.3"));
		}
	};
}