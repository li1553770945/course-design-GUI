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
	const char* GetISBN()const;
	const char* GetName()const;
	const char* GetAuth()const;
	const char* GetPub()const;
};
class BookData :public TitleInfo {//书的所有信息，可变的，数量等
protected:

	char _date_added[15];
	int _qty;
	double _whosale, _retail;//批发价、零售价
public:
	void SetDateAdded(const char* const&);
	void SetQty(int);
	void SetWholesale(double);
	void SetRetail(double);
	const char* GetDateAdded()const;
	double GetWholesale()const;
	double GetRetail()const;
	int GetQty()const;
	bool operator <(const BookData& rhs)const;

};
class Sale;
class ShoppingItem
{
	const BookData* _book_ptr_;
	int _num_;
public:
	ShoppingItem(const BookData* ptr, int num);
	friend Sale;
};
class Sale {
public:
	enum AddStatus { //表示添加状态的常数
	};
	static constexpr AddStatus SUCCESS = static_cast<AddStatus>(0x01);
	static constexpr AddStatus EXIST = static_cast<AddStatus>(0x02);
	static constexpr AddStatus OVERQTY = static_cast<AddStatus>(0x04);
	Sale();
	double GetSum();
	double GetSumFaxed();
	static double GetFax();
	static void SetFax(double fax);
	void Sattle();
	void AddItem(const BookData* &,int& num,int& status,int& row);//既要返回状态，又要返回插入行，是在无奈，出此对策，传进来状态和行数的引用
	bool IsEmpty();
	const BookData* choose_book;
	int FindItem(const BookData*);
private:
	vector <ShoppingItem> _cart_;//购物车
	static double _fax_;
	double _sum_;
};

class Management {
public:
	static bool FindISBN(set<BookData> const &, set<BookData>::iterator  &,const char* const&);//根据ISBN查找书
	static bool FindISBN(set<BookData>const&,  const char* const&);//根据ISBN查找书
};
