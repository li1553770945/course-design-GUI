#include "../GUIh/BookInfoWindow.h"
BookInfoWindow::BookInfoWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	book = NULL;
}
void BookInfoWindow::Set()
{
	ui.Name->setText(QString::fromLocal8Bit(book->GetName()));
	ui.Author->setText(QString::fromLocal8Bit(book->GetAuth()));
	ui.Publisher->setText(QString::fromLocal8Bit(book->GetPub()));
	ui.ISBN->setText(QString(book->GetISBN()));
	ui.DateAdded->setText(QString(book->GetDateAdded()));
	ui.Retail->setText(QString::number(book->GetRetail(),10,2));
	ui.Wholesale->setText(QString::number(book->GetWholesale(),10,2));
	ui.Qty->setText(QString::number(book->GetQty()));
}
void BookInfoWindow::ReceiveBookPtr(Sale* ptr)
{
	book = ptr;
	Set();
}
