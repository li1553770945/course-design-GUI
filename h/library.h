#pragma once
#include <bits/stdc++.h>
using namespace std;

class TitleInfo {//书的基本信息，固定
protected:
	char _isbn[13], _name[51], _author[31], _publisher[31];
public:
	void SetName(const char* const& name);
	void SetISBN(const char* const& isbn);
	void SetAuthor(const char* const& author);
	void SetPub(const char* const& publisher);
	const char* GetISBN();
	const char* GetName();
	const char* GetAuth();
	const char* GetPub();
};
class BookData :public TitleInfo {//书的所有信息，可变的，数量等
protected:

	char _date_added[11];
	int _qty;
	double _whosale, _retail;//批发价、零售价
public:
	void SetDateAdded(const char* const&);
	void SetQty(int);
	void SetWholesale(double);
	void SetRetail(double);
	const char* GetDateAdded();
	double GetWholesale();
	double GetRetail();
	int GetQty();

};
class Sale :public BookData {
	static double _fax_rate_;
public:
	static void SaleMoudle(list<Sale>& books);
	Sale(Sale const& obj);
	Sale();
	static double GetFaxRate();
	static void SetFaxRate(double fax_rate);
};
class Management {
public:
	static list<Sale>::iterator FindISBN(list<Sale>::iterator const &, list<Sale>::iterator const &,const char* const&);//根据ISBN查找书
	static list<Sale>::iterator FindName(list<Sale>::iterator const & , list<Sale>::iterator const&,const char* const&);
	static list<Sale>::iterator FuzzySearch(list<Sale>::iterator const& begin, list<Sale>::iterator const& end, const char* const& str);//模糊查找，书名、出版社、作者中包含关键字
	static list<Sale>::iterator FuzzySearchName(list<Sale>::iterator const& begin, list<Sale>::iterator const& end, const char* const& name);//模糊查找，书名中包含关键字
	static void FuzzySearch(list<Sale> & books);//实现模糊查找
	static void LookUpBook(list<Sale>&books);//实现根据书名精确查找
	static void DeleteBook(list<Sale>&books);//删除书
	static void AddBook(list<Sale>&books);//添加一本书
	static void EditBook(list<Sale>&books);//编辑书
	static void BookInfo(Sale* const& book);//输出一本书的信息
	static void ChangeFaxRate();//改变税率
};
class Report {
public:
	static void ListAll(list<Sale>const& books);
	static void ListWholesale(list<Sale>const& books);
	static void ListRetial(list<Sale>const& books);
	static void SortQty(list <Sale> & books);
	static void SortWholesale(list<Sale>& books);
	static void SortDate(list<Sale>& books);
};
extern list<Sale> books;