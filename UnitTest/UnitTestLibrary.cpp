#include "pch.h"
#include "CppUnitTest.h"
#include "../h/library.h"
#include "../h/global.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibrary
{

	TEST_CLASS(TestSale)
	{
	BookData book1, book2;
	 BookData* p1 = &book1, * p2 = &book2;
	public:
		
		TEST_METHOD(AddNotExist)
		{
			Sale sale;
			book1.SetQty(10);
			int num = 10, status, row;
			sale.AddItem(p1, num, status, row);
			Assert::AreEqual((int)Sale::SUCCESS, status);
			Assert::AreEqual(0, row);
		}
		TEST_METHOD(AddNotExistOverQty)
		{
			Sale sale;
			book1.SetQty(10);
			int num = 15, status, row;
			sale.AddItem(p1, num, status, row);
			Assert::AreEqual((int)Sale::OVERQTY, status);
		}
		TEST_METHOD(AddExist)
		{
			Sale sale;
			book1.SetQty(10);
			int num = 5, status, row;
			sale.AddItem(p1, num, status, row);
			sale.AddItem(p1, num, status, row);
			Assert::AreEqual((int)Sale::SUCCESS|Sale::EXIST, status);
			Assert::AreEqual(0, row);
		}
		TEST_METHOD(AddExistOverQty)
		{
			Sale sale;
			book1.SetQty(10);
			int num = 10, status, row;
			sale.AddItem(p1, num, status, row);
			sale.AddItem(p1, num, status, row);
			Assert::AreEqual((int)Sale::EXIST|Sale::OVERQTY, status);
		}
		TEST_METHOD(Sum)
		{
			Sale sale;
			book1.SetQty(10);
			book1.SetRetail(2.5);
			int num = 10, status, row;
			sale.AddItem(p1, num, status, row);
			Assert::AreEqual(25.0, sale.GetSum());
			Assert::AreEqual(25.0*(sale.GetFax()+1), sale.GetSumFaxed());
		}
		TEST_METHOD(Sattle)
		{
			Sale sale;
			book1.SetQty(20);
			book1.SetRetail(2.5);
			int num = 10, status, row;
			sale.AddItem(p1, num, status, row);
			sale.Sattle();
			Assert::AreEqual(true, sale.IsEmpty());
			Assert::AreEqual(10, book1.GetQty());
		}
	};
	TEST_CLASS(TestManagement)
	{
		TEST_METHOD(Add)
		{
			BookData* book = new BookData;
			Management::Add(book);
			Assert::AreEqual(1, (int)books.size());
		}
		TEST_METHOD(FindISBNNoIterator)
		{
			char isbn[10] = "123";
			BookData* book = new BookData;
			book->SetISBN(isbn);
			Assert::IsFalse(Management::FindISBN(string(isbn)));
			Assert::IsTrue(Management::Add(book));
			Assert::IsTrue(Management::FindISBN(string(isbn)));
			
		}
		TEST_METHOD(FindISBNHasIterator)
		{
			char isbn[10] = "1234";
			BookData* book = new BookData;
			book->SetISBN(isbn);
			Assert::IsFalse(Management::FindISBN(string(isbn)));
			Assert::IsTrue(Management::Add(book));
			BooksIt it;
			Assert::IsTrue(Management::FindISBN(it,string(isbn)));

		}
		TEST_METHOD(Delete)
		{
			BookData* book = new BookData;
			char isbn[10] = "12345";
			book->SetISBN(isbn);
			Management::Add(book);
			BooksIt it;
			Assert::IsTrue(Management::FindISBN(it, string(isbn)));
			Management::Delete(it);
		}
	};
}
