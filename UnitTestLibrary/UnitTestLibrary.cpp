#include "pch.h"
#include "CppUnitTest.h"
#include "../h/library.h"
#include "../cpp/TitleInfo.cpp"
#include "../cpp/BookData.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTestLibrary
{
	TEST_CLASS(UnitTestLibrary)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BookData* book = new BookData;
			book->SetISBN("123");
			Assert::AreEqual("12", book->GetISBN());
		}
	};
}
