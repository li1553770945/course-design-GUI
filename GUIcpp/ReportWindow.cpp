#include "../GUIh/ReportWindow.h"
#include "../h/global.h"
#include <QtWidgets\qmessagebox.h>
# pragma execution_character_set("utf-8")
ReportWindow::ReportWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	SetData();
}
void ReportWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("report"));
}
void ReportWindow::on_CheckBoxName_clicked()
{
	if(ui.CheckBoxName->isChecked())
		ui.Table->setColumnHidden(0, false);
	else
		ui.Table->setColumnHidden(0, true);
}
void ReportWindow::on_CheckBoxISBN_clicked()
{
	if (ui.CheckBoxISBN->isChecked())
		ui.Table->setColumnHidden(1, false);
	else
		ui.Table->setColumnHidden(1, true);
}
void ReportWindow::on_CheckBoxAuthor_clicked()
{
	if (ui.CheckBoxAuthor->isChecked())
		ui.Table->setColumnHidden(2, false);
	else
		ui.Table->setColumnHidden(2, true);
}
void ReportWindow::on_CheckBoxPublisher_clicked()
{
	if (ui.CheckBoxPublisher->isChecked())
		ui.Table->setColumnHidden(3, false);
	else
		ui.Table->setColumnHidden(3, true);
}
void ReportWindow::on_CheckBoxDateAdded_clicked()
{
	if (ui.CheckBoxDateAdded->isChecked())
		ui.Table->setColumnHidden(4, false);
	else
		ui.Table->setColumnHidden(4, true);
}
void ReportWindow::on_CheckBoxQty_clicked()
{
	if (ui.CheckBoxQty->isChecked())
		ui.Table->setColumnHidden(5, false);
	else
		ui.Table->setColumnHidden(5, true);
}

void ReportWindow::on_CheckBoxRetail_clicked()
{
	if (ui.CheckBoxRetail->isChecked())
		ui.Table->setColumnHidden(6, false);
	else
		ui.Table->setColumnHidden(6, true);
}
void ReportWindow::on_CheckBoxWholesale_clicked()
{
	if (ui.CheckBoxWholesale->isChecked())
		ui.Table->setColumnHidden(7, false);
	else
		ui.Table->setColumnHidden(7, true);
}
void ReportWindow::on_ButtonFlush_clicked()
{
	SetData();
}
void ReportWindow::SetData()
{
	clock_t start=clock();
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
	//ui.Table->clear();
	ui.Table->setRowCount(books.size());
	int row_count = 0;
	for (auto book_pair:books)
	{
		BookData* book = &*book_pair.second;
		ui.Table->setItem(row_count, 0,new QTableWidgetItem(QString::fromLocal8Bit(book->GetName())));
		ui.Table->setItem(row_count, 1, new QTableWidgetItem(book->GetISBN()));
		ui.Table->setItem(row_count, 2, new QTableWidgetItem(QString::fromLocal8Bit(book->GetAuth())));
		ui.Table->setItem(row_count, 3, new QTableWidgetItem(QString::fromLocal8Bit(book->GetPub())));
		ui.Table->setItem(row_count, 4, new QTableWidgetItem(book->GetDateAdded()));
		ui.Table->setItem(row_count, 5, new QTableWidgetItem(QString::number(book->GetQty())));
		ui.Table->setItem(row_count, 6, new QTableWidgetItem(QString::number(book->GetRetail(),10,2)));
		ui.Table->setItem(row_count, 7, new QTableWidgetItem(QString::number(book->GetWholesale(), 10, 2)));
		for (int j = 0; j < 8; j++)
		{
			ui.Table->item(row_count, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		row_count++;
	}
	ui.Table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	clock_t end = clock();		//程序结束用时
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	ui.statusbar->showMessage(QString("书库中共有") + QString::number(row_count) + QString("本书，加载耗时")+QString::number(endtime,10,3)+QString("秒"));
}