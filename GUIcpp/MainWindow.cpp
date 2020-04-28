#include "../GUIh/MainWindow.h"
#include "../GUIh/SaleWindow.h"
#include "../GUIh/ReportWindow.h"
#include "../GUIh/ManageWindow.h"
#include "../GUIh/AboutWindow.h"
#include "../h/global.h"
#include <qmessagebox.h>
#include <QTextCodec>
#include <QCloseEvent> 
#include <qdebug.h>
#include <io.h>
# pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	sale_window=NULL;
	manage_window = NULL;
	report_window=NULL;
	LoadFile();
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::LoadFile()
{
	try {
		OpenFile();
	}
	catch (FileStatus err)
	{
		if(err==FileStatus::CANNOTOPEN)//无法打开文件
		{
			QMessageBox box(QMessageBox::Critical, "错误", "无法打开文件！");
			box.exec();
			exit(EXIT_FAILURE);
		}
		if (err == FileStatus::NOTEXIST)//文件不存在，就先尝试创建
		{
			QMessageBox box(QMessageBox::Warning, "警告", "书库文件不存在，将尝试创建");
			box.exec();
			try//尝试创建
			{
				CreateFile();
			}
			catch (FileStatus error)
			{
				if (error == FileStatus::CANNOTCREATE)//创建失败
				{
					QMessageBox box(QMessageBox::Critical, "错误", "无法创建书库文件！");
					box.exec();
					exit(EXIT_FAILURE);
				}
			}
			try//创建成功，尝试打开
			{
				OpenFile();
			}
			catch (FileStatus error)
			{
				QMessageBox box(QMessageBox::Critical, "错误", "无法打开文件！");
				box.exec();
				exit(EXIT_FAILURE);
			}
			
		}
	}
}
void MainWindow::on_ButtonSale_clicked()
{
	if (manage_window != NULL)//为了防止收银的同时进行修改，规定收银和管理窗口智能同时打开一个
	{
		QMessageBox box(QMessageBox::Information, "提示", "请先关闭管理窗口！");
		box.exec();
		return;
	}
	if (sale_window == NULL)//如果为空，说明还没有打开过这个窗口，那么就新建一个并显示
	{
		
		sale_window = new SaleWindow;
		connect(sale_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		sale_window->show();
		
	}
	else//如果已经打开了，不再重新创建，而是显示原来的
	{
		sale_window->showNormal();
		sale_window->activateWindow();

	}
}
void MainWindow::on_ButtonManage_clicked()
{
	if (sale_window != NULL)
	{
		QMessageBox box(QMessageBox::Information, "提示", "请先关闭收银窗口！");
		box.exec();
		return;
	}
	if (manage_window == NULL)
	{

		manage_window = new ManageWindow;
		connect(manage_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		manage_window->show();

	}
	else
	{
		manage_window->showNormal();
		manage_window->activateWindow();
	}
}
void MainWindow::on_ButtonReport_clicked()
{
	if (report_window == NULL)
	{
		report_window = new ReportWindow;
		connect(report_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		report_window->show();
	}
	else
	{
		report_window->showNormal();
		report_window->activateWindow();
	}
}
void MainWindow::on_ButtonExit_clicked()
{
	QMessageBox messageBox(QMessageBox::Warning,"警告", "您确定要退出吗?这将关闭所有当前打开的窗口！",QMessageBox::Yes | QMessageBox::No, NULL); 
	switch (messageBox.exec())
	{
	case QMessageBox::Yes:
	{
		if (manage_window)
		{
			manage_window->close();
			delete manage_window;
		}
		if (report_window)
		{
			report_window->close();
			delete report_window;
		}
		if (sale_window)
		{
			sale_window->close();
			delete sale_window;
		}
		SaveFile();
		exit(0);
	}
	default:
		return;
	}
}
void MainWindow::closeEvent(QCloseEvent* event)
{
	
	on_ButtonExit_clicked();
	event->ignore();
}
void MainWindow::CloseSon(std::string name)
{
	if (name == "sale")
	{
		sale_window = NULL;
	}
	else if (name == "manage")
	{
		manage_window = NULL;
	}
	else if (name == "report")
	{
		report_window = NULL;
	}
}
void MainWindow::on_About_triggered()
{
	AboutWindow* about_window = new AboutWindow;
	about_window->exec();
}
