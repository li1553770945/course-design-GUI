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
class Management {
public:
	static set<BookData>::iterator FindISBN(set<BookData>::iterator const &, set<BookData>::iterator const &,const char* const&);//����ISBN������
	static set<BookData>::iterator FindName(set<BookData>::iterator const & , set<BookData>::iterator const&,const char* const&);
	static set<BookData>::iterator FuzzySearch(set<BookData>::iterator const& begin, set<BookData>::iterator const& end, const char* const& str);//ģ�����ң������������硢�����а����ؼ���
	static set<BookData>::iterator FuzzySearchName(set<BookData>::iterator const& begin, set<BookData>::iterator const& end, const char* const& name);//ģ�����ң������а����ؼ���

};
