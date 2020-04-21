#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include "../h/library.h"
#include <iostream>
#include "../h/global.h"
#include "../GUIh//BookInfoWindow.h"
#include "../GUIh/ReportWindow.h"
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	book = NULL;
}
void SaleWindow::on_Confirm_clicked()
{
	set<BookData>::iterator it = Management::FindISBN(books.begin(), books.end(), ui.ISBN->text().toLatin1().data());
	if (it == books.end())
	{
		QMessageBox message_box(QMessageBox::Warning, "提示", "ISBN输入错误，请重新输入!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		book = &*it;
		ui.Name->setText(QString::fromLocal8Bit(it->GetName()));
		ui.Qty->setText(QString::number(it->GetQty()));
		ui.Retail->setText(QString::number(it->GetRetail(),10,2));
	}
}
void SaleWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("sale"));
}
void SaleWindow::on_ISBN_returnPressed()
{
	on_Confirm_clicked();
}
void SaleWindow::on_ButtonDetail_clicked()
{
	if (book == NULL)
	{
		QMessageBox box(QMessageBox::Information, "提示", "请先选择一本书");
		box.exec();
	}
	else
	{
		BookInfoWindow* book_info_window = new BookInfoWindow;
		connect(this, SIGNAL(SendBookPtr(const BookData*)), book_info_window, SLOT(ReceiveBookPtr(const BookData*)));
		emit SendBookPtr(book);
		book_info_window->exec();
	}
}
void SaleWindow::on_ButtonLibrary_clicked()
{
	ReportWindow *report_window=new ReportWindow ;
	report_window->show();
}