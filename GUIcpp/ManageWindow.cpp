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
	BookData book;
	try
	{
		QByteArray ba = ui.NameAdd->text().toLocal8Bit();
		book.SetName(ba.data());//��������

		if (Management::FindISBN(books.begin(), books.end(), ui.ISBNAdd->text().toLatin1().data()) != books.end())
		{
			QMessageBox box(QMessageBox::Information, "��ʾ", "��ISBN�Ѿ����ڣ�");
			box.exec();
		}
		book.SetISBN(ui.ISBNAdd->text().toLatin1().data());

		ba = ui.AuthorAdd->text().toLocal8Bit();//��������
		book.SetAuthor(ba.data());

		ba = ui.PublisherAdd->text().toLocal8Bit();//���ó�����
		book.SetPub(ba.data());//���ó�����
		book.SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));//���ÿ��
		book.SetRetail(atof(ui.RetailAdd->text().toLatin1().data()));//�������ۼ�
		book.SetWholesale(atof(ui.WholesaleAdd->text().toLatin1().data()));//����������
		book.SetDateAdded(ui.DateAddedAdd->text().toLatin1().data());//���ý�������
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "��ʾ", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	cout << book.GetName();
	books.insert(book);
	QList<QLineEdit*> line_list = ui.TabAdd->findChildren<QLineEdit*>();
	for (auto line_edit : line_list)
	{
		line_edit->setText("");
	}
	QMessageBox box(QMessageBox::Information, "��ʾ", "��ӳɹ���");
	box.exec();
}