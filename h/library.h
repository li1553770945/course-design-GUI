#pragma once
#include <bits/stdc++.h>
using namespace std;

class TitleInfo {//��Ļ�����Ϣ���̶�
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
class BookData :public TitleInfo {//���������Ϣ���ɱ�ģ�������
protected:

	char _date_added[15];
	int _qty;
	double _whosale, _retail;//�����ۡ����ۼ�
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
class Sale {
private:
	static double _fax_;
public:
	static double GetFax();
	static void SetFax(double fax);
};
class Management {
public:
	static bool FindISBN(set<BookData> const &, set<BookData>::iterator  &,const char* const&);//����ISBN������
	static bool FindISBN(set<BookData>const&,  const char* const&);//����ISBN������
};
