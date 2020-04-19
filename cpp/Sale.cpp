#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include "../h/library.h"
#include <windows.h>
using namespace std;
double Sale::_fax_rate_ = 0.06;
unique_ptr<char>  GetTime()
{

	time_t rawtime;
	struct tm* ptminfo;
	time(&rawtime);
	ptminfo = localtime(&rawtime);
	char* p = new char[30];
	sprintf(p, "%02d-%02d-%02d %02d:%02d:%02d\n",
		ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
	unique_ptr <char> smart_p(p);
	return smart_p;
}

Sale::Sale(Sale const& obj)
{
	strcpy(_name, obj._name);
	strcpy(_isbn, obj._isbn);
	strcpy(_author, obj._author);
	strcpy(_publisher, obj._publisher);
	strcpy(_date_added, obj._date_added);
	_whosale = obj._whosale;
	_retail = obj._retail;
	_qty = obj._qty;
}
Sale::Sale()
{

}
double Sale::GetFaxRate()
{
	return _fax_rate_;
}
void Sale::SetFaxRate(double fax_rate)
{
	_fax_rate_ = fax_rate;
}
void Sale::SaleMoudle(list<Sale>& books)
{
	class SaleList {
	public:
		int num;
		list<Sale>::iterator it;
	};
	cout << "     ����ģ��" << endl;
	vector <SaleList> sale_list;
	while (true)//����ģ��while
	{
		cout << "��������ͼ���ISBN���" << endl;
		cout << "�������֪��ͼ���ISBN��ţ���ʹ�ò��ҹ��ܡ�" << endl;
		cout << "���롰find����ʼ��ȷ���ң����롰fuzzy��ģ������" << endl;
		cout << "���롰exit���˳�����ģ�飨����ѡ����嵥���ᱻ���棩" << endl;
		cout << "���롰continue��ȡ��ѡ��" << endl;
		cout << "�����룺";
		string isbn;
		cin >> isbn;
		if (isbn == "find")
		{
			Management::LookUpBook(books);
			continue;
		}
		else if (isbn == "fuzzy")
		{
			Management::FuzzySearch(books);
			continue;
		}
		else if (isbn == "exit")
		{
			cout << "��ȷ��Ҫ�˳�ô����������ѡ�������ᱻ���棡" << endl;
			cout << "ȷ�������롰Y��";
			string confirm;
			cin >> confirm;
			if (confirm == "Y")
				return;
		}
		list<Sale>::iterator it = Management::FindISBN(books.begin(), books.end(), isbn.data());
		if (it == books.end())
		{
			cout << "��Ǹ��û���ҵ���ISBN�����Ӧ��ͼ�顣" << endl;
		}
		else if (find_if(sale_list.begin(), sale_list.end(), [it](SaleList const  & rhs) {return rhs.it==it;})!=sale_list.end())
		{
			cout << "��Ҫ�����Ѿ������б��У������޸ģ���ѡ���޸�ѡ��"<<endl;
		}
		else
		{
			int qty = it->GetQty();
			if (qty == 0)
			{
				cout << endl << "��Ǹ���Ȿ��̫���Ѿ����۹���!" << endl << endl;
			}
			else
			{
				Management::BookInfo(&*it);
				cout << "��������Ҫ���������(1~" << qty << "������0����ʾ��������" << endl;
				int n = -1;
				cin >> n;
				while (n<0 || n>qty)
				{
					if (n < 0)
						cout << "�����������������:";
					else if (n > qty)
						cout << "��Ǹ����ǰ��治�㣬����������:";
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					cin >> n;
				}
				if (n == 0)
				{
					cout << "��������" << endl;
				}
				else
				{
					sale_list.push_back({ n,it });
				}
			}

		}
	
		while (true)//ѡ�������Ĳ���while
		{
			cout << GetTime();//��ȡ��ǰʱ��
			cout << "���  ����    ISBN��      ����               ����   ���" << endl << endl;
			double money = 0;
			int id_num = 1;
			for (auto book : sale_list)
			{
				cout << "  " << id_num++ << "    " << book.num << "     " << book.it->GetISBN() << "       " << book.it->GetName() << "      " << book.it->GetRetail() << "   " << book.num * book.it->GetRetail() << endl;
				money += book.num * book.it->GetRetail();
			}
			cout << endl << "-----------------------------------------------------------------" << endl << endl;
			cout << "���ۺϼ� RMB��" << money << endl;
			cout << "����˰��RMB��" << money * GetFaxRate() << endl;
			money += money * GetFaxRate();
			cout << "Ӧ���ܶRMB��" << money << endl;
			cout << "��ѡ��������Ĳ���" << endl;
			cout << "1.��������ͼ��" << endl;
			cout << "2.����ͼ������������ȡ������ĳ�飬��ѡ����" << endl;
			cout << "3.����" << endl;
			cout << "4.���������˳��������嵥���ᱻ���棩" << endl;
			string next;
			cout << "�����룺";
			cin >> next;
			while (atoi(next.data()) < 1 || atoi(next.data()) > 4)
			{
				cout << "����������������룺";
				cin >> next;
			}
			int nex = atoi(next.data());//��nextת������
			if (nex == 1)
			{
				break;
			}
			else if (nex == 2)
			{
				cout << "��ѡ��Ҫ�޸ĵ�ͼ����ţ�" << endl;
				string id;
				cin >> id;
				while (atoi(id.data()) < 1 || atoi(id.data()) > id_num - 1)
				{
					cout << "�����������������";
					cin >> id;
				}

				vector<SaleList>::iterator  edit_book = sale_list.begin() + atoi(id.data()) - 1;//ָ��sale_list��Ҫ�༭����ĵ�����
				Management::BookInfo(&*edit_book->it);
				int qty = edit_book->it->GetQty();//Ҫ�༭�����Ŀ��
				cout << "������Ҫ�����������0-" << qty << "�������롰0����ʾȡ������:";
				int edit_num = -1;
				cin >> edit_num;
				while (edit_num<0 || edit_num>qty)
				{
					if (edit_num < 0)
						cout << "�����������������:";
					else if (edit_num > qty)
						cout << "��Ǹ����ǰ��治�㣬����������:";
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					cin >> edit_num;
				}

				if (edit_num == 0)
					sale_list.erase(edit_book);
				else
					edit_book->num = edit_num;

			}
			else if (nex == 3 )
			{
				if (!sale_list.empty())
				{
					for (auto book : sale_list)
					{
						book.it->SetQty(book.it->GetQty() - book.num);

					}
					cout << "�����ѳɹ���" << endl;
					Sleep(3000);
				}
				return;
			}
			else if (nex == 4)
			{
				cout << "��ȷ��Ҫ�˳�ô����������ѡ�������ᱻ���棡" << endl;
				cout << "ȷ�������롰Y��";
				string confirm;
				cin >> confirm;
				if (confirm == "Y")
					return;
			}

		}
	}
}
