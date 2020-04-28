#include "../GUIh/FindWindow.h"
#include "../h/library.h"
#include <qmessagebox.h>
# pragma execution_character_set("utf-8")
FindWindow::FindWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}
void FindWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("find"));
}
void FindWindow::on_ButtonFind_clicked()
{
	if (!ui.CheckBoxName->isChecked()&&!ui.CheckBoxAuthor->isChecked()&& ui.CheckBoxPublisher->isChecked())
	{
		QMessageBox box(QMessageBox::Information, "提示", "至少选择一个查找项！");
		box.exec();
		return;
	}
	map <Management::FindWhere, bool >find_where;
	if (ui.CheckBoxName->isChecked())
		find_where[Management::FindWhere::NAME] = true;
	if (ui.CheckBoxAuthor->isChecked())
		find_where[Management::FindWhere::AUTHOR] = true;
	if (ui.CheckBoxPublisher->isChecked())
		find_where[Management::FindWhere::PUBLISHER] = true;
	QByteArray ba = ui.LineEditContent->text().toLocal8Bit();
	_find_content_ = ba.data();
	if (ui.RadioEqual->isChecked())
	{
		Management::FindEqual(_find_results_, _find_content_, find_where);
	}
	else if (ui.RadioInclude->isChecked())
	{
		Management::FindInclude(_find_results_, _find_content_, find_where);
	}
	SetTable();
}
void  FindWindow::SetTable()
{
	ui.Table->clearContents();
	ui.Table->setRowCount(0);
	int row = 0;
	for (auto book : _find_results_)
	{
		ui.Table->insertRow(row);
		ui.Table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit(book->GetName())));//添加表格
		ui.Table->setItem(row, 1, new QTableWidgetItem(QString(book->GetISBN())));
		ui.Table->setItem(row, 2, new QTableWidgetItem(QString::fromLocal8Bit(book->GetAuth())));
		ui.Table->setItem(row, 3, new QTableWidgetItem(QString::fromLocal8Bit(book->GetPub())));
		ui.Table->setItem(row, 4, new QTableWidgetItem(QString::number(book->GetQty(),10)));
		row++;
	}
	ui.statusbar->showMessage(QString("搜索“")+QString::fromLocal8Bit(_find_content_.data())+QString("”共找到")+QString::number(_find_results_.size())+QString("个结果"));
}
void FindWindow::on_LineEditContent_returnPressed()
{
	on_ButtonFind_clicked();
}