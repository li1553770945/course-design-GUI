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
	cout << "     销售模块" << endl;
	vector <SaleList> sale_list;
	while (true)//整个模块while
	{
		cout << "请您输入图书的ISBN编号" << endl;
		cout << "如果您不知道图书的ISBN编号，可使用查找功能。" << endl;
		cout << "输入“find”开始精确查找，输入“fuzzy”模糊查找" << endl;
		cout << "输入“exit”退出收银模块（您已选择的清单不会被保存）" << endl;
		cout << "输入“continue”取消选书" << endl;
		cout << "请输入：";
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
			cout << "您确定要退出么？您的所有选书结果不会被保存！" << endl;
			cout << "确定请输入“Y：";
			string confirm;
			cin >> confirm;
			if (confirm == "Y")
				return;
		}
		list<Sale>::iterator it = Management::FindISBN(books.begin(), books.end(), isbn.data());
		if (it == books.end())
		{
			cout << "抱歉，没有找到此ISBN编码对应的图书。" << endl;
		}
		else if (find_if(sale_list.begin(), sale_list.end(), [it](SaleList const  & rhs) {return rhs.it==it;})!=sale_list.end())
		{
			cout << "您要的书已经存在列表中，如需修改，请选择修改选项"<<endl;
		}
		else
		{
			int qty = it->GetQty();
			if (qty == 0)
			{
				cout << endl << "抱歉，这本书太火，已经被售光啦!" << endl << endl;
			}
			else
			{
				Management::BookInfo(&*it);
				cout << "请输入您要购买的数量(1~" << qty << "），“0”表示放弃购买" << endl;
				int n = -1;
				cin >> n;
				while (n<0 || n>qty)
				{
					if (n < 0)
						cout << "输入错误，请重新输入:";
					else if (n > qty)
						cout << "抱歉，当前库存不足，请重新输入:";
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max)(), '\n');
					cin >> n;
				}
				if (n == 0)
				{
					cout << "放弃购买" << endl;
				}
				else
				{
					sale_list.push_back({ n,it });
				}
			}

		}
	
		while (true)//选书结束后的操作while
		{
			cout << GetTime();//获取当前时间
			cout << "序号  数量    ISBN号      书名               单价   金额" << endl << endl;
			double money = 0;
			int id_num = 1;
			for (auto book : sale_list)
			{
				cout << "  " << id_num++ << "    " << book.num << "     " << book.it->GetISBN() << "       " << book.it->GetName() << "      " << book.it->GetRetail() << "   " << book.num * book.it->GetRetail() << endl;
				money += book.num * book.it->GetRetail();
			}
			cout << endl << "-----------------------------------------------------------------" << endl << endl;
			cout << "销售合计 RMB：" << money << endl;
			cout << "零售税：RMB：" << money * GetFaxRate() << endl;
			money += money * GetFaxRate();
			cout << "应付总额：RMB：" << money << endl;
			cout << "请选择接下来的操作" << endl;
			cout << "1.继续购买图书" << endl;
			cout << "2.更改图书数量（如需取消购买某书，请选择此项）" << endl;
			cout << "3.结算" << endl;
			cout << "4.放弃购买并退出（您的清单不会被保存）" << endl;
			string next;
			cout << "请输入：";
			cin >> next;
			while (atoi(next.data()) < 1 || atoi(next.data()) > 4)
			{
				cout << "输入错误，请重新输入：";
				cin >> next;
			}
			int nex = atoi(next.data());//将next转成整形
			if (nex == 1)
			{
				break;
			}
			else if (nex == 2)
			{
				cout << "请选择要修改的图书序号：" << endl;
				string id;
				cin >> id;
				while (atoi(id.data()) < 1 || atoi(id.data()) > id_num - 1)
				{
					cout << "输入错误，请重新输入";
					cin >> id;
				}

				vector<SaleList>::iterator  edit_book = sale_list.begin() + atoi(id.data()) - 1;//指向sale_list中要编辑的书的迭代器
				Management::BookInfo(&*edit_book->it);
				int qty = edit_book->it->GetQty();//要编辑的数的库存
				cout << "请输入要购买的数量（0-" << qty << "），输入“0”表示取消购买:";
				int edit_num = -1;
				cin >> edit_num;
				while (edit_num<0 || edit_num>qty)
				{
					if (edit_num < 0)
						cout << "输入错误，请重新输入:";
					else if (edit_num > qty)
						cout << "抱歉，当前库存不足，请重新输入:";
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
					cout << "交易已成功！" << endl;
					Sleep(3000);
				}
				return;
			}
			else if (nex == 4)
			{
				cout << "您确定要退出么？您的所有选书结果不会被保存！" << endl;
				cout << "确定请输入“Y：";
				string confirm;
				cin >> confirm;
				if (confirm == "Y")
					return;
			}

		}
	}
}
