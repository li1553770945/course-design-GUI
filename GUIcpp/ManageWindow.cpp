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
		book.SetName(ba.data());//设置书名

		if (Management::FindISBN(books.begin(), books.end(), ui.ISBNAdd->text().toLatin1().data()) != books.end())
		{
			QMessageBox box(QMessageBox::Information, "提示", "该ISBN已经存在！");
			box.exec();
		}
		book.SetISBN(ui.ISBNAdd->text().toLatin1().data());

		ba = ui.AuthorAdd->text().toLocal8Bit();//设置作者
		book.SetAuthor(ba.data());

		ba = ui.PublisherAdd->text().toLocal8Bit();//设置出版社
		book.SetPub(ba.data());//设置出版社
		book.SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));//设置库存
		book.SetRetail(atof(ui.RetailAdd->text().toLatin1().data()));//设置零售价
		book.SetWholesale(atof(ui.WholesaleAdd->text().toLatin1().data()));//设置批发价
		book.SetDateAdded(ui.DateAddedAdd->text().toLatin1().data());//设置进货日期
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
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
	QMessageBox box(QMessageBox::Information, "提示", "添加成功！");
	box.exec();
}