#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include "../h/library.h"
#include <iostream>
#include "../h/global.h"
#include "../GUIh//BookInfoWindow.h"
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	book = NULL;
}
void SaleWindow::on_Confirm_clicked()
{
	qDebug() << "确定按钮";
	list<Sale>::iterator it = Management::FindISBN(books.begin(), books.end(), ui.ISBN->text().toLatin1().data());
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
		BookInfoWindow* book_info_window = new BookInfoWindow();
		connect(this, SIGNAL(SendBookPtr(Sale*)), book_info_window, SLOT(ReceiveBookPtr(Sale*)));
		emit SendBookPtr(book);
		book_info_window->show();
	}
}