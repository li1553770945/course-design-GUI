#include "../GUIh/SaleWindow.h"
#include <qevent.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include "../h/library.h"
#include <iostream>
# pragma execution_character_set("utf-8")
SaleWindow::SaleWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
		qDebug() << it->GetQty();
		std::cout << it->GetName();
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