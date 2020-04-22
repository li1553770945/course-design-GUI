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
			Assert::AreEqual(12.5, my_atof("12.5"));
			Assert::AreEqual(-1.0, my_atof("double"));
		}
	};
}
