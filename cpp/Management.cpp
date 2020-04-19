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
	cout << "***********�������*************" << endl;
	cout << "I S B N��" << it->GetISBN()<<endl;
	cout << "��    ����" << it->GetName() << endl;
	cout << "��    �ߣ�" << it->GetAuth() << endl;
	cout << "�� �� �磺" << it->GetPub() << endl;
	cout << "�������ڣ�" << it->GetDateAdded() << endl;
	cout << "�� �� ����" << it->GetQty() << endl;
	cout << "�� �� �ۣ�" << it->GetWholesale() << endl;
	cout << "�� �� �ۣ�" << it->GetRetail() << endl<<endl;

}
void Management::LookUpBook(list<Sale>& books)
{	
	string name;
	cout << "������Ҫ���ҵ��������:";
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
	cout << "���ҵ�" << found << "�����" << endl;
}
void Management::AddBook(list<Sale>& books)
{
	Sale temp;
	string str;
	cout << "������ISBN��ţ�";
	while (1)
	{
		try
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cin >> str;
			if (FindISBN(books.begin(), books.end(), str.data()) != books.end())
			{
				cout << "��Ǹ����ISBN�Ѿ����ڣ���Ҫ��������ô?�����롰Y��:";
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
			cout << err << "���������룺";
		}
	}
	cout << "������������";
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
			cout << err << "���������룺";
		}
	}
	cout << "��������������";
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
			cout << err << "���������룺";
		}
	}
	
	cout << "����������磺";
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
			cout << err << "���������룺";
		}
	}
	cout << "������������ڣ�";
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
			cout << err << "���������룺";
		}
	}
	cout << "�������棺";
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
			cout << err << "���������룺";
		}
	}
	cout << "���������ۼۣ�";
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
			cout << err << "���������룺";
		}
	}
	cout << "�����������ۣ�";
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
			cout << err << "���������룺";
		}
	}
	books.push_back(temp);
	cout << "��ӳɹ���" << endl;
}
void Management::DeleteBook(list<Sale>& books)
{
	string isbn;
	cout << "������Ҫɾ�������ISBN����:";
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
		cout << "��Ǹ��û���ҵ���Ҫ����" << endl;
		return;
	}
	else if (found == 1)
	{
		it = results[0];
	}
	else if (found != 1)
	{
		cout << "�ҵ��˶౾�飬��������Ҫɾ������ţ�";
		int which=0;
		cin >> which;
		while (which <= 0 || which > found)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�����������������";
			cin >> which;
		}
		it = results[which - 1];
	}
	cout<<"��ȷ��Ҫɾ����ȷ�������롰Y��:";
	string confirm;
	cin >> confirm;
	if (confirm == "Y")
	{
		books.erase(it);
		cout << "ɾ���ɹ���" << endl;
		return;
	}
	cout << "ȡ��ɾ����" << endl;
	
}
void Management::EditBook(list <Sale>& books)
{
	string isbn;
	vector<list<Sale>::iterator> results;
	cout << "������Ҫ�༭�����ISBN����:";
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
		cout << "��Ǹ��û���ҵ���Ҫ����" << endl;
		return;
	}
	else if (found == 1)
	{
		it = results[0];
	}
	else if (found != 1)
	{
		cout << "�ҵ��˶౾�飬��������Ҫ�༭����ţ�";
		int which = 0;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (which <= 0 || which > found);
		{
			cout << "�����������������";
			cin >> which;
		}
		it = results[which - 1];
	}
	cout << "������༭�������Ϣ���������޸�ĳ���ֱ�Ӱ��»س�"<<endl;
	string str;
	Sale &temp=*it;
	cout << "������ISBN��ţ�";
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
					cout << "��Ǹ��ϵͳ�����������ͬISBN������������:" << endl;
					continue;
				}
				temp.SetISBN(str.data());
			}
			break;
		}
		catch (const char* err)
		{
			cout << err << "���������룺";
		}
	}
	cout << "������������";
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
			cout << err << "���������룺";
		}
	}
	cout << "��������������";
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
			cout << err << "���������룺";
		}
	}
	
	cout << "����������磺";
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
			cout << err << "���������룺";
		}
	}
	cout << "������������ڣ�";
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
			cout << err << "���������룺";
		}
	}
	cout << "�������棺";
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
			cout << err << "���������룺";
		}
	}
	cout << "���������ۼۣ�";
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
			cout << err << "���������룺";
		}
	}
	cout << "�����������ۣ�";
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
			cout << err << "���������룺";
		}
	}
	cout << "�޸ĳɹ���"<<endl;
}
void Management::FuzzySearch(list<Sale>  & books)
{
	cout << "��Ҫ����ģ�����ҷ�ʽ��"<<endl;
	cout << "1.��������а����ؼ���"<< endl;
	cout << "2.������֡����������������������ؼ���"<<endl;
	cout << "������:" ;
	int command=0;
	cin >> command;
	while (command<1||command>2)
	{
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(),'\n');
		cout << "����������������룺" ;
		cin >> command;
	}
	string str;
	cout << "������ؼ���:";
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
		cout << "Ϊ���ҵ����½��:" << endl;
		for (auto iterator : results)
		{
			BookInfo(&*iterator);
		}
		cout << "��Ϊ���ҵ�" << found << "�����" << endl;
	}
	else
	{
		cout << "��Ǹ��û���ҵ����" << endl;
	}
}
void Management::ChangeFaxRate()
{
	cout <<setprecision(3)<<fixed<< "��ǰ˰��" << Sale::GetFaxRate();
	cout << setprecision(2) << fixed;
	cout << "�������µ�˰��:(С����ʽ��" ;
	string str;
	cin >> str;
	Sale::SetFaxRate(atof(str.data()));
}