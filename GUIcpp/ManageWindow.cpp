#include "../GUIh/ManageWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
#include "../h/global.h"
# pragma execution_character_set("utf-8")
ManageWindow::ManageWindow(QWidget* parent):QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.DateAddedAdd->setDate(QDate::currentDate());
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
		if (Management::FindISBN(books,  ui.ISBNAdd->text().toLatin1().data()))
		{
			QMessageBox box(QMessageBox::Information, "提示", "该ISBN已经存在！");
			box.exec();
			return;
		}
		book.SetISBN(ui.ISBNAdd->text().toLatin1().data());

		ba = ui.AuthorAdd->text().toLocal8Bit();//设置作者
		book.SetAuthor(ba.data());

		ba = ui.PublisherAdd->text().toLocal8Bit();//设置出版社
		book.SetPub(ba.data());//设置出版社
		book.SetQty(my_atoi(ui.QtyAdd->text().toLatin1().data()));//设置库存
		book.SetRetail(my_atof(ui.RetailAdd->text().toLatin1().data()));//设置零售价
		book.SetWholesale(my_atof(ui.WholesaleAdd->text().toLatin1().data()));//设置批发价
		ba = ui.DateAddedAdd->date().toString("yyyy-MM-dd").toLatin1(); // must
		book.SetDateAdded(ba.data());//设置进货日期
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	books.insert(book);
	/*QList<QLineEdit*> line_list = ui.TabAdd->findChildren<QLineEdit*>();
	for (auto line_edit : line_list)
	{
		line_edit->setText("");
	}*/
	QMessageBox box(QMessageBox::Information, "提示", "添加成功！");
	box.exec();
}
void ManageWindow::on_ButtonISBNConfirm_clicked()
{
	set<BookData>::iterator it; 
	if (!Management::FindISBN(books,it, ui.ISBNInput->text().toLatin1().data()))
	{
		QMessageBox message_box(QMessageBox::Warning, "提示", "ISBN输入错误，请重新输入!", QMessageBox::Yes);
		message_box.exec();
	}
	else
	{
		ui.ButtonSave->setEnabled(true);
		ui.ButtonDelete->setEnabled(true);
		current_edit_book = it;
		ui.NameEdit->setText(QString::fromLocal8Bit(it->GetName()));
		ui.ISBNEdit->setText(QString::fromLocal8Bit(it->GetISBN()));
		ui.PublisherEdit->setText(QString::fromLocal8Bit(it->GetPub()));
		ui.AuthorEdit->setText(QString::fromLocal8Bit(it->GetAuth()));
		ui.QtyEdit->setText(QString::number(it->GetQty()));
		ui.RetailEdit->setText(QString::number(it->GetRetail(), 10, 2));
		ui.WholesaleEdit->setText(QString::number(it->GetWholesale(), 10, 2));
		ui.DateAddedEdit->setDate(QDate::fromString(QString(it->GetDateAdded()), "yyyy-MM-dd"));
	}
}
void ManageWindow::on_ButtonDelete_clicked()
{
	QMessageBox box(QMessageBox::Warning, "警告", "您确定要删除么？此操作不可恢复！",QMessageBox::Yes| QMessageBox::No);
	switch (box.exec())
	{
		case QMessageBox::Yes:
		{
			books.erase(current_edit_book);
			ui.ButtonSave->setEnabled(false);
			ui.ButtonDelete->setEnabled(false);
			QList<QLineEdit*> line_list = ui.TabEdit->findChildren<QLineEdit*>();
			for (auto line_edit : line_list)
			{
				line_edit->setText("");
			}
			QMessageBox success(QMessageBox::Information, "提示", "删除成功！");
			success.exec();
		}
			break;
		default:
			return;
	}

}
void ManageWindow::on_ISBNInput_returnPressed()
{
	on_ButtonISBNConfirm_clicked();
}
void ManageWindow::on_ButtonSave_clicked()
{
	BookData book;
	try
	{
		QByteArray ba = ui.NameEdit->text().toLocal8Bit();
		book.SetName(ba.data());//设置书名
		set<BookData>::iterator find_it;
			
		if (!Management::FindISBN(books,find_it, ui.ISBNEdit->text().toLatin1().data())&&find_it!=current_edit_book)
		{
			QMessageBox box(QMessageBox::Information, "提示", "该ISBN已经存在！");
			box.exec();
			return;
		}
		book.SetISBN(ui.ISBNEdit->text().toLatin1().data());

		ba = ui.AuthorEdit->text().toLocal8Bit();//设置作者
		book.SetAuthor(ba.data());

		ba = ui.PublisherEdit->text().toLocal8Bit();//设置出版社
		book.SetPub(ba.data());//设置出版社
		book.SetQty(my_atoi(ui.QtyEdit->text().toLatin1().data()));//设置库存
		book.SetRetail(my_atof(ui.RetailEdit->text().toLatin1().data()));//设置零售价
		book.SetWholesale(my_atof(ui.WholesaleEdit->text().toLatin1().data()));//设置批发价
		ba = ui.DateAddedEdit->date().toString("yyyy-MM-dd").toLatin1(); // must
		book.SetDateAdded(ba.data());//设置进货日期
	}
	catch (const char* err)
	{
		QMessageBox box(QMessageBox::Warning, "提示", QString::fromLocal8Bit(err));
		box.exec();
		return;
	}
	books.erase(current_edit_book);
	current_edit_book=books.insert(book).first;
	QMessageBox box(QMessageBox::Information, "提示", "修改成功！");
	box.exec();
}