#include "pch.h"
#include "CppUnitTest.h"
#include "../h/library.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibrary
{

	TEST_CLASS(TestSale)
	{
	BookData book1, book2;
	const BookData* p1 = &book1, * p2 = &book2;
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
	};
}
