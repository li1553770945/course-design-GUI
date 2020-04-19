#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
void Report::ListAll(list<Sale> const & books)
{
	int index = 1;
	for (auto book : books)
	{	
		cout <<"序号："<< index << endl;
		Management::BookInfo(&book);
		if (!(index % 2))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "按下回车键继续，或者输入“q”退出：";
			string command;
			getline(cin,command);
			if (command == "q")
				return;
		}
		index++;
	}
	cout << "书库共有" << index -1<< "本书" << endl;
}
void Report::ListWholesale(list<Sale>const& books)
{
	double sum=0;
	int id=1;
	for(auto book:books)
	{
		cout << "序号：" << id++ << endl;
		cout << "批发价：" << book.GetWholesale() << endl;
		cout << "库存量：" << book.GetQty() << endl<<endl;
		sum += book.GetWholesale();
	}
	cout << "总批发价：" << sum<<endl;
 }
void Report::ListRetial(list<Sale>const& books)
{
	double sum = 0;
	int id = 1;
	for (auto book : books)
	{
		cout << "序号：" << id++ << endl;
		cout << "零售价：" << book.GetRetail() << endl;
		cout << "库存量：" << book.GetQty() << endl << endl;
		sum += book.GetRetail();
	}
	cout << "总零售价：" << sum << endl;
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
		cout << "批发价：" << book.GetWholesale () << endl;
		cout << "库存量：" << book.GetQty() << endl;
		sum+=book.GetWholesale();
	}
	cout << "总批发价：" << sum << endl;
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
		cout << "进货日期：" << book.GetDateAdded() << endl;
	}
}
