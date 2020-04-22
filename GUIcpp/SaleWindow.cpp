#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include "../h/library.h"
#include <iostream>
#include "../h/global.h"
#include "../GUIh//BookInfoWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../h/global.h"
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	sum_money = 0;
	sum_money_faxed = 0;
	fax = Sale::GetFax();
	ui.Fax->setText(QString::number(fax, 10, 2));
	select = false;
}
void SaleWindow::on_Confirm_clicked()
{
	set<BookData>::iterator it;
	if (!Management::FindISBN(books, it, ui.ISBN->text().toLatin1().data()))
	{
		QMessageBox message_box(QMessageBox::Warning, "提示", "ISBN输入错误，请重新输入!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		select_book = it;
		ui.ButtonDetail->setEnabled(false);
		ui.ButtonAddToCart->setEnabled(false);
		ui.Name->setText(QString::fromLocal8Bit(it->GetName()));
		ui.Qty->setText(QString::number(it->GetQty()));
		ui.Retail->setText(QString::number(it->GetRetail(),10,2));
		Select(true);
	}
}
void SaleWindow::closeEvent(QCloseEvent* event)
{
	if (ui.TableCart->rowCount() != 0)
	{
		QMessageBox box(QMessageBox::Warning, "警告", "您的购物车有待结算的物品，退出后将不会保存！您确定要退出么？", QMessageBox::Yes | QMessageBox::No);
		switch (box.exec())
		{
		case QMessageBox::Yes:
			emit Close(std::string("sale"));
			break;
		default:
			event->ignore();
		}
	}
	else
	{
		emit Close(std::string("sale"));
	}
	
}
void SaleWindow::on_ISBN_returnPressed()
{
	on_Confirm_clicked();
}
void SaleWindow::on_ButtonDetail_clicked()
{
		BookInfoWindow* book_info_window = new BookInfoWindow;
		connect(this, SIGNAL(SendBookPtr(const BookData*)), book_info_window, SLOT(ReceiveBookPtr(const BookData*)));
		emit SendBookPtr(&*select_book);
		book_info_window->exec();
}
void SaleWindow::on_ButtonLibrary_clicked()
{
	ReportWindow *report_window=new ReportWindow ;
	report_window->show();
}
void SaleWindow::on_ButtonAddToCart_clicked()
{
	QByteArray ba = ui.Num->text().toLatin1(); // must
	int num = my_atoi(ba.data());
	if (num <= 0)
	{
		QMessageBox box(QMessageBox::Information, "提示", "数量必须为大于等于0的整数！");
		box.exec();
		return;
	}
	bool has_bought = false;
	for(int i=0;i<cart.size();i++)
	{
		if (cart[i].book == select_book)
		{
			if (num +cart[i].num > select_book->GetQty())
			{
				char tip[200];
				sprintf(tip, "您已经购买此书，位于购物车第%d列，购买数量为%d,您购买此书的总量已经超过库存！",i+1,cart[i].num);
				QMessageBox box(QMessageBox::Information, "提示", tip);
				box.exec();
				return;
			}
			sum_money += num * select_book->GetRetail();//计算总金额
			sum_money_faxed = sum_money * (1 + fax);
			ui.Sum->setText(QString::number(sum_money, 10, 2));
			ui.SumFaxed->setText(QString::number(sum_money_faxed, 10, 2));

			num += cart[i].num;//将更正后的数量更新在窗口
			ui.TableCart->setItem(i, 2, new QTableWidgetItem(QString::number(num)));
			ui.TableCart->setItem(i, 3, new QTableWidgetItem(QString::number(select_book->GetRetail() * num, 10, 2)));
			cart[i].num = num;//更正购物车里的数量
			has_bought = true;
			break;
		}
	}
	if (!has_bought)
	{
		if (num > select_book->GetQty())
		{
			QMessageBox box(QMessageBox::Information, "提示", "当前库存不足！");
			box.exec();
			return;
		}
		int row_count = ui.TableCart->rowCount();
		ui.TableCart->insertRow(row_count);
		//ui.Table->item(row_count,)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.TableCart->setItem(row_count, 0, new QTableWidgetItem(QString::fromLocal8Bit(select_book->GetName())));//添加表格
		ui.TableCart->setItem(row_count, 1, new QTableWidgetItem(QString::number(select_book->GetRetail(), 10, 2)));
		ui.TableCart->setItem(row_count, 2, new QTableWidgetItem(QString::number(num)));
		ui.TableCart->setItem(row_count, 3, new QTableWidgetItem(QString::number(select_book->GetRetail() * num, 10, 2)));
		sum_money += num * select_book->GetRetail();//计算总金额
		sum_money_faxed = sum_money * (1 + fax);
		ui.Sum->setText(QString::number(sum_money, 10, 2));
		ui.SumFaxed->setText(QString::number(sum_money_faxed, 10, 2));

		Cart item;//真的添加到购物车
		item.book = select_book;
		item.num = num;
		cart.push_back(item);
	}
	ui.Num->setText("");//添加到购物车后，清空当前信息
	ui.Retail->setText("");
	ui.Name->setText("");
	ui.Qty->setText("");
	ui.ISBN->setText("");
	Select(false);
}
void SaleWindow::on_Num_returnPressed()
{
	if(select)
		on_ButtonAddToCart_clicked();
	else
	{
		QMessageBox box(QMessageBox::Information, "提示", "请先选择一本书！");
		box.exec();
	}
}
void SaleWindow::on_ButtonSattle_clicked()
{
	if (!cart.empty())
	{
		for (auto item : cart)
		{
			auto it = const_cast<BookData&>(*item.book);
			cout << item.book->GetQty() << endl;
			it.SetQty(10);
			cout << item.num << endl;
			cout << item.book->GetQty();
		}
		ui.TableCart->clearContents();
		ui.TableCart->setRowCount(0);
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		cart.clear();
		sum_money = 0;
		QMessageBox box(QMessageBox::Information, "提示", "交易已成功！");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "提示", "当前购物车为空！");
		box.exec();
	}
}
void SaleWindow::Select(bool flag)
{
	if (flag == false)
	{
		select = false;
		ui.ButtonAddToCart->setEnabled(false);
		ui.ButtonDetail->setEnabled(false);
	}
	else
	{
		select = true;
		ui.ButtonAddToCart->setEnabled(true);
		ui.ButtonDetail->setEnabled(true);
	}
}