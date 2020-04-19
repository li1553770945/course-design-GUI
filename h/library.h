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
	const char* GetISBN();
	const char* GetName();
	const char* GetAuth();
	const char* GetPub();
};
class BookData :public TitleInfo {//���������Ϣ���ɱ�ģ�������
protected:

	char _date_added[11];
	int _qty;
	double _whosale, _retail;//�����ۡ����ۼ�
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
	static list<Sale>::iterator FindISBN(list<Sale>::iterator const &, list<Sale>::iterator const &,const char* const&);//����ISBN������
	static list<Sale>::iterator FindName(list<Sale>::iterator const & , list<Sale>::iterator const&,const char* const&);
	static list<Sale>::iterator FuzzySearch(list<Sale>::iterator const& begin, list<Sale>::iterator const& end, const char* const& str);//ģ�����ң������������硢�����а����ؼ���
	static list<Sale>::iterator FuzzySearchName(list<Sale>::iterator const& begin, list<Sale>::iterator const& end, const char* const& name);//ģ�����ң������а����ؼ���
	static void FuzzySearch(list<Sale> & books);//ʵ��ģ������
	static void LookUpBook(list<Sale>&books);//ʵ�ָ���������ȷ����
	static void DeleteBook(list<Sale>&books);//ɾ����
	static void AddBook(list<Sale>&books);//���һ����
	static void EditBook(list<Sale>&books);//�༭��
	static void BookInfo(Sale* const& book);//���һ�������Ϣ
	static void ChangeFaxRate();//�ı�˰��
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