#include "pch.h"
#include "CppUnitTest.h"
#include "../h/global.h"
#include "../cpp/global.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGlobal
{
	TEST_CLASS(UnitTestGlobal)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(123, my_atoi("123"));
			Assert::AreEqual(-1, my_atoi("测试"));
			Assert::AreEqual(-1.0, my_atof("测试"));
			Assert::AreEqual(666.6, my_atof("666.6"));
		}
	};
}
