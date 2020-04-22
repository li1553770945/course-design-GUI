#include "pch.h"
#include "CppUnitTest.h"
#include "../h/library.h"
#include "../cpp/TitleInfo.cpp"
#include "../cpp/BookData.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace TestBookData
{
	TEST_CLASS(ISBN)
	{
	public:
		
		TEST_METHOD(String)
		{
			BookData* book = new BookData;
			book->SetISBN("123");
			Assert::AreEqual("123", book->GetISBN());
		}
	};
	TEST_CLASS(Books)
	{
	public:
		set<BookData> books;
		BookData* book = new BookData;
		TEST_METHOD(Change)
		{
			book->SetName("name");
			books.insert(*book);
			set<BookData>::iterator it = books.begin();
			auto p = const_cast<BookData&>(*it);
			p.SetName("name_change");
			Assert::AreEqual("name_change", p.GetName());
			Assert::AreEqual("name_change", it->GetName());
		}
	};
}
