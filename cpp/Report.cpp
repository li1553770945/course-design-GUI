#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void Report::ListAll(list<Sale> const & books)
{
	int index = 1;
	for (auto book : books)
	{	
		cout <<"��ţ�"<< index << endl;
		Management::BookInfo(&book);
		if (!(index % 2))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "���»س����������������롰q���˳���";
			string command;
			getline(cin,command);
			if (command == "q")
				return;
		}
		index++;
	}
	cout << "��⹲��" << index -1<< "����" << endl;
}
void Report::ListWholesale(list<Sale>const& books)
{
	double sum=0;
	int id=1;
	for(auto book:books)
	{
		cout << "��ţ�" << id++ << endl;
		cout << "�����ۣ�" << book.GetWholesale() << endl;
		cout << "�������" << book.GetQty() << endl<<endl;
		sum += book.GetWholesale();
	}
	cout << "�������ۣ�" << sum<<endl;
 }
void Report::ListRetial(list<Sale>const& books)
{
	double sum = 0;
	int id = 1;
	for (auto book : books)
	{
		cout << "��ţ�" << id++ << endl;
		cout << "���ۼۣ�" << book.GetRetail() << endl;
		cout << "�������" << book.GetQty() << endl << endl;
		sum += book.GetRetail();
	}
	cout << "�����ۼۣ�" << sum << endl;
}
bool SortByQty(Sale &a,Sale &b)
{
	return a.GetQty() > b.GetQty();
}
void Report::SortQty(list<Sale>& books)
{
	books.sort(SortByQty);
	int i = 1;
	for(auto book:books)
	{
		cout << i++<<":";
		cout << book.GetQty()<<endl;
	}
}
bool SortByWholesale(Sale& a, Sale& b)
{
	return a.GetWholesale() > b.GetWholesale();
}
void Report::SortWholesale(list<Sale>& books)
{
	books.sort(SortByWholesale);
	int i = 1;
	double sum=0;
	for (auto book : books)
	{
		cout << i++ << ":";
		cout << "�����ۣ�" << book.GetWholesale () << endl;
		cout << "�������" << book.GetQty() << endl;
		sum+=book.GetWholesale();
	}
	cout << "�������ۣ�" << sum << endl;
}
bool SortByDate(Sale& a, Sale& b)
{
	return strcmp(a.GetDateAdded(),b.GetDateAdded())>0;
}
void Report::SortDate(list<Sale>& books)
{
	books.sort(SortByDate);
	int i = 1;
	for (auto book : books)
	{
		cout << i++ << ":";
		cout << "�������ڣ�" << book.GetDateAdded() << endl;
	}
}
