#include <bits/stdc++.h>
#include "../h/library.h"
using namespace std;
list<Sale>::iterator Management::FindISBN(list<Sale>::iterator const& begin, list<Sale>::iterator const& end,const char* const& isbn)
{
	return find_if(begin, end, [isbn](Sale& rhs) {return !strcmp(rhs.GetISBN(), isbn); });
}
list<Sale>::iterator Management::FindName(list<Sale>::iterator const& begin, list<Sale>::iterator const& end,const char* const& name)
{
	return find_if(begin, end, [name](Sale& rhs) {return !strcmp(rhs.GetName(), name); });
}
list<Sale>::iterator Management::FuzzySearch(list<Sale>::iterator const& begin, list<Sale>::iterator const& end, const char* const& name)
{
	return find_if(begin, end, [name](Sale& rhs) {return string(rhs.GetName()).find(name)!=string::npos|| string(rhs.GetAuth()).find(name) != string::npos || string(rhs.GetPub()).find(name) != string::npos; });
}
list<Sale>::iterator Management::FuzzySearchName(list<Sale>::iterator const& begin, list<Sale>::iterator const& end, const char* const& name)
{
	return find_if(begin, end, [name](Sale& rhs) {return string(rhs.GetName()).find(name) != string::npos; });
}
void Management::BookInfo(Sale* const & it)
{
	cout << "***********书的资料*************" << endl;
	cout << "I S B N：" << it->GetISBN()<<endl;
	cout << "书    名：" << it->GetName() << endl;
	cout << "作    者：" << it->GetAuth() << endl;
	cout << "出 版 社：" << it->GetPub() << endl;
	cout << "进书日期：" << it->GetDateAdded() << endl;
	cout << "库 存 量：" << it->GetQty() << endl;
	cout << "批 发 价：" << it->GetWholesale() << endl;
	cout << "零 售 价：" << it->GetRetail() << endl<<endl;

}
void Management::LookUpBook(list<Sale>& books)
{	
	string name;
	cout << "请输入要查找的书的名称:";
	cin >>name;
	int found = 0;
	list<Sale>::iterator it= books.begin();
	do
	{
		it = FindName(it, books.end(), name.c_str());
		if (it != books.end())
		{
			found++;
			cout << "        " << found << endl;
			BookInfo(&*it);
			it++;
		}
	} while (it != books.end());
	cout << "共找到" << found << "个结果" << endl;
}
void Management::AddBook(list<Sale>& books)
{
	Sale temp;
	string str;
	cout << "请输入ISBN编号：";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> str;
			if (FindISBN(books.begin(), books.end(), str.data()) != books.end())
			{
				cout << "抱歉，该ISBN已经存在，您要重新输入么?请输入“Y”:";
				string confirm;
				cin >> confirm;
				if (confirm == "Y")
				{
					continue;
				}
				else
				{
					return;
				}


			}
			temp.SetISBN(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入书名：";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> str;
			temp.SetName(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入作者名：";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> str;
			temp.SetAuthor(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	
	cout << "请输入出版社：";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> str;
			temp.SetPub(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入进货日期：";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> str;
			temp.SetDateAdded(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入库存：";
	while (1)
	{
		int num;
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> num;
			temp.SetQty(num);
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入零售价：";
	while (1)
	{
		double price;
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> price;
			temp.SetRetail(price);
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入批发价：";
	while (1)
	{
		double price;
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> price;
			temp.SetWholesale(price);
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	books.push_back(temp);
	cout << "添加成功！" << endl;
}
void Management::DeleteBook(list<Sale>& books)
{
	string isbn;
	cout << "请输入要删除的书的ISBN编码:";
	cin >> isbn;
	int found = 0;
	vector <list<Sale>::iterator> results;
	list<Sale>::iterator it = books.begin();
	do
	{
		it = FindISBN(it, books.end(), isbn.data());
		if (it != books.end())
		{
			found++;
			cout << "        " << found << endl;
			BookInfo(&*it);
			results.push_back(it);
			it++;
		}
	} while (it != books.end());
	if (found==0)
	{
		cout << "抱歉，没有找到您要的书" << endl;
		return;
	}
	else if (found == 1)
	{
		it = results[0];
	}
	else if (found != 1)
	{
		cout << "找到了多本书，请输入您要删除的序号：";
		int which=0;
		cin >> which;
		while (which <= 0 || which > found)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入错误，请重新输入";
			cin >> which;
		}
		it = results[which - 1];
	}
	cout<<"您确定要删除？确定请输入“Y”:";
	string confirm;
	cin >> confirm;
	if (confirm == "Y")
	{
		books.erase(it);
		cout << "删除成功！" << endl;
		return;
	}
	cout << "取消删除。" << endl;
	
}
void Management::EditBook(list <Sale>& books)
{
	string isbn;
	vector<list<Sale>::iterator> results;
	cout << "请输入要编辑的书的ISBN编码:";
	cin >>isbn;
	int found = 0;
	list<Sale>::iterator it = books.begin();
	do
	{
		it = FindISBN(it, books.end(),isbn.data());
		if (it != books.end())
		{
			found++;
			cout << "        " << found << endl;
			BookInfo(&*it);
			results.push_back(it);
			it++;
		}
	} while (it != books.end());
	if (found == 0)
	{
		cout << "抱歉，没有找到您要的书" << endl;
		return;
	}
	else if (found == 1)
	{
		it = results[0];
	}
	else if (found != 1)
	{
		cout << "找到了多本书，请输入您要编辑的序号：";
		int which = 0;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (which <= 0 || which > found);
		{
			cout << "输入错误，请重新输入";
			cin >> which;
		}
		it = results[which - 1];
	}
	cout << "请输入编辑后书的信息，若无需修改某项，请直接按下回车"<<endl;
	string str;
	Sale &temp=*it;
	cout << "请输入ISBN编号：";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			getline(cin, str);
			if (!str.empty())
			{

				list<Sale>::iterator it = FindISBN(books.begin(), books.end(), str.data());
				if (it != books.end())
				{
					cout << "抱歉，系统不允许存在相同ISBN，请重新输入:" << endl;
					continue;
				}
				temp.SetISBN(str.data());
			}
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入书名：";
	while (1)
	{
		try
		{
			getline(cin,str);
			if(!str.empty())
				temp.SetName(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入作者名：";
	while (1)
	{
		try
		{
			getline(cin, str);
			if (!str.empty())
			temp.SetAuthor(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	
	cout << "请输入出版社：";
	while (1)
	{
		try
		{
			getline(cin, str);
			if (!str.empty())
			temp.SetPub(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入进货日期：";
	while (1)
	{
		try
		{
			getline(cin, str);
			if (!str.empty())
			temp.SetDateAdded(str.data());
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入库存：";
	while (1)
	{
		int num;
		try
		{
			getline(cin, str);
			if (!str.empty())
			{
				num = atoi(str.data());
				temp.SetQty(num);
			}
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入零售价：";
	while (1)
	{
		double price;
		try
		{
			getline(cin, str);
			if (!str.empty())
			{
				price = atof(str.data());
				temp.SetRetail(price);
			}
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "请输入批发价：";
	while (1)
	{
		double price;
		try
		{
			getline(cin, str);
			if (!str.empty())
			{
				price = atof(str.data());
				temp.SetWholesale(price);
			}
			break;
		}
		catch (const char* err)
		{
			cout << err << "请重新输入：";
		}
	}
	cout << "修改成功！"<<endl;
}
void Management::FuzzySearch(list<Sale>  & books)
{
	cout << "您要那种模糊查找方式？"<<endl;
	cout << "1.书的名字中包含关键字"<< endl;
	cout << "2.书的名字、作者名、出版社名包含关键字"<<endl;
	cout << "请输入:" ;
	int command=0;
	cin >> command;
	while (command<1||command>2)
	{
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(),'\n');
		cout << "输入错误，请重新输入：" ;
		cin >> command;
	}
	string str;
	cout << "请输入关键字:";
	cin >> str;
	list<Sale>::iterator it=books.begin();
	vector<list<Sale>::iterator> results;
	int found = 0;
	do
	{
		it = command==1?FuzzySearchName(it, books.end(), str.data()): FuzzySearch(it, books.end(), str.data());
		if (it != books.end())
		{
			results.push_back(it);
			it++;
			found++;
		}
	} while (it != books.end());
	if (found)
	{
		cout << "为您找到以下结果:" << endl;
		for (auto iterator : results)
		{
			BookInfo(&*iterator);
		}
		cout << "共为您找到" << found << "个结果" << endl;
	}
	else
	{
		cout << "抱歉，没有找到结果" << endl;
	}
}
void Management::ChangeFaxRate()
{
	cout <<setprecision(3)<<fixed<< "当前税率" << Sale::GetFaxRate();
	cout << setprecision(2) << fixed;
	cout << "请输入新的税率:(小数形式）" ;
	string str;
	cin >> str;
	Sale::SetFaxRate(atof(str.data()));
}