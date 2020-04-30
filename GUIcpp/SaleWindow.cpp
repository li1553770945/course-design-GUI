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
#include "../GUIh/FindWindow.h"
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	ui.Fax->setText(QString::number(Sale::GetFax(), 10, 2));
	select = false;
	find_window = NULL;
	report_window = NULL;
	ui.TableCart->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.TableCart->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}
void SaleWindow::on_Confirm_clicked()
{
	BooksIt it;
	if (!Management::FindISBN(it, ui.ISBN->text().toStdString()))
	{
		QMessageBox message_box(QMessageBox::Warning, "提示", "ISBN输入错误，请重新输入!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		_sale_.choose_book =&*(it->second);
		ui.Name->setText(QString::fromLocal8Bit(_sale_.choose_book->GetName()));
		ui.Qty->setText(QString::number(_sale_.choose_book->GetQty()));
		ui.Retail->setText(QString::number(_sale_.choose_book->GetRetail(),10,2));
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
		emit SendBookPtr(&*_sale_.choose_book);
		book_info_window->exec();
}
void SaleWindow::on_ButtonLibrary_clicked()
{
	if (report_window == NULL)
	{
		report_window = new ReportWindow;
		connect(report_window, SIGNAL(Close(std::string)), this, SLOT(SonClose(std::string)));
		report_window->show();
	}
	else
	{
		report_window->showNormal();
		report_window->activateWindow();
	}
}
void SaleWindow::on_ButtonAddToCart_clicked()
{

	QByteArray ba = ui.Num->text().toLatin1(); // must
	int num = my_atoi(ba.data());
	if (num <= 0)
	{
		QMessageBox box(QMessageBox::Information, "提示", "数量必须为大于0的整数！");
		box.exec();
		return;
	}
	
	ui.TableCart->disconnect(SIGNAL(cellChanged(int,int)));
	int status;
	int row;
	_sale_.AddItem(_sale_.choose_book, num, status, row);
	if (status== Sale::SUCCESS||status==(Sale::EXIST|Sale::SUCCESS))
	{
		if (row >= ui.TableCart->rowCount())
		{
			ui.TableCart->insertRow(row);
		}
		ui.TableCart->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit(_sale_.choose_book->GetName())));//添加表格
		ui.TableCart->setItem(row, 1, new QTableWidgetItem(QString::number(_sale_.choose_book->GetRetail(), 10, 2)));
		ui.TableCart->setItem(row, 2, new QTableWidgetItem(QString::number(num)));
		ui.TableCart->setItem(row, 3, new QTableWidgetItem(QString::number(_sale_.choose_book->GetRetail() * num, 10, 2)));
		for (int j = 0; j < 4; j++)
		{
			ui.TableCart->item(row, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		ui.TableCart->item(row, 0)->setFlags(Qt::NoItemFlags);
		ui.TableCart->item(row, 1)->setFlags(Qt::NoItemFlags);
		ui.TableCart->item(row, 3)->setFlags(Qt::NoItemFlags);
		ui.Sum->setText(QString::number(_sale_.GetSum(), 10, 2));
		ui.SumFaxed->setText(QString::number(_sale_.GetSumFaxed() ,10, 2));
		ui.ISBN->setText("");
		ui.Num->setText("");
	}
	else if (status == Sale::OVERQTY)
	{
		QMessageBox box(QMessageBox::Information, "提示", "您的购买量已经超过库存！");
		box.exec();
	}
	else if (status == Sale::OVERQTY|Sale::EXIST)
	{
		char message[100];
		sprintf(message,"购物车已经存在此书，位于第%d行,加上已经购买的数量，您的购买量已经超过库存！",row+1);
		QMessageBox box(QMessageBox::Information, "提示", message);
		box.exec();
	}
	connect(ui.TableCart, SIGNAL(cellChanged(int, int)), this, SLOT(on_TableCart_cellChanged(int,int)));
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
void SaleWindow::on_ButtonSattle_clicked()//结算按钮
{
	if(!_sale_.IsEmpty())
	{
		_sale_.Sattle();
		ui.TableCart->clearContents();
		ui.TableCart->setRowCount(0);
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		QMessageBox box(QMessageBox::Information, "提示", "交易已成功！");
		box.exec();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "提示", "当前购物车为空！");
		box.exec();
	}
}
void SaleWindow::Select(bool flag)//改变当前是否已经选择一本书（在最上面，不是在表格中选择）
{
	if (flag == false)
	{
		select = false;
		ui.ButtonAddToCart->setEnabled(false);//如果没有选择，那么添加到购物车和详细信息按钮将不可使用
		ui.ButtonDetail->setEnabled(false);
	}
	else
	{
		select = true;
		ui.ButtonAddToCart->setEnabled(true);
		ui.ButtonDetail->setEnabled(true);
	}
}
void SaleWindow::on_ButtonFind_clicked()
{
	if (find_window == NULL)
	{
		find_window = new FindWindow;
		connect(find_window, SIGNAL(Close(std::string)), this, SLOT(SonClose(std::string)));
		find_window->show();
	}
	else
	{
		find_window->showNormal();
		find_window->activateWindow();
	}
}
void SaleWindow::SonClose(std::string name)
{
	if (name == "report")
	{
		report_window = NULL;
	}
	if (name == "find")
	{
		find_window = NULL;
	}
}
void SaleWindow::on_TableCart_cellChanged(int row, int column)
{
	QMessageBox box(QMessageBox::Information, "提示", "您的购买量已经超过库存！");
	box.exec();//TODO:不能区分用户编辑还是初始化数据
}
void SaleWindow::on_ButtonClear_clicked()
{
	QMessageBox box(QMessageBox::Warning, "警告", "您确定要放弃支付并清空购物车么？该操作不可恢复！",QMessageBox::Yes|QMessageBox::No);
	switch (box.exec())
	{
	case QMessageBox::Yes:
		ui.TableCart->clearContents();
		ui.TableCart->setRowCount(0);
		ui.Sum->setText("");
		ui.SumFaxed->setText("");
		_sale_.Clear();
	}
}