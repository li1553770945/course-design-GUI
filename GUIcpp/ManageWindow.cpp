#include "../GUIh/ManageWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include "../h/global.h"
# pragma execution_character_set("utf-8")
ManageWindow::ManageWindow(QWidget* parent):QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}
void ManageWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("manage"));
}
void ManageWindow::on_ButtonAdd_clicked()
{
	Sale book;
	try 
	{
		QByteArray ba = ui.NameAdd->text().toLocal8Bit();
		book.SetName(ba.data());
	}
	catch (const char * err)
	{
		QMessageBox box(QMessageBox::Warning,"提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置书名
	try
	{
		QByteArray ba = ui.ISBNAdd->text().toLocal8Bit();
		book.SetISBN(ba.data());
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置ISBN
	try
	{
		QByteArray ba = ui.AuthorAdd->text().toLocal8Bit();
		book.SetAuthor(ba.data());
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置作者
	try
	{
		QByteArray ba = ui.PublisherAdd->text().toLocal8Bit();
		book.SetPub(ba.data());
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置出版社
	try
	{
		book.SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置库存
	try
	{
		book.SetRetail(atof(ui.RetailAdd->text().toLatin1().data()));
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置零售价
	try
	{
		book.SetWholesale(atof(ui.NameAdd->text().toLatin1().data()));
	}//TODO:不能解决输入错误
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置批发价
	try
	{
		book.SetDateAdded(ui.DateAddedAdd->text().toLatin1().data());
	}//TODO:不能解决输入错误
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//设置批发价
	cout << book.GetName();
	books.push_back(book);
	QMessageBox box(QMessageBox::Information, "提示", "添加成功！");
	box.exec();
}