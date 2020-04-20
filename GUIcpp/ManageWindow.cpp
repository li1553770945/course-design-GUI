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
		QMessageBox box(QMessageBox::Warning,"��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//��������
	try
	{
		QByteArray ba = ui.ISBNAdd->text().toLocal8Bit();
		book.SetISBN(ba.data());
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//����ISBN
	try
	{
		QByteArray ba = ui.AuthorAdd->text().toLocal8Bit();
		book.SetAuthor(ba.data());
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//��������
	try
	{
		QByteArray ba = ui.PublisherAdd->text().toLocal8Bit();
		book.SetPub(ba.data());
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//���ó�����
	try
	{
		book.SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//���ÿ��
	try
	{
		book.SetRetail(atof(ui.RetailAdd->text().toLatin1().data()));
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//�������ۼ�
	try
	{
		book.SetWholesale(atof(ui.NameAdd->text().toLatin1().data()));
	}//TODO:���ܽ���������
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//����������
	try
	{
		book.SetDateAdded(ui.DateAddedAdd->text().toLatin1().data());
	}//TODO:���ܽ���������
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}//����������
	cout << book.GetName();
	books.push_back(book);
	QMessageBox box(QMessageBox::Information, "��ʾ", "��ӳɹ���");
	box.exec();
}