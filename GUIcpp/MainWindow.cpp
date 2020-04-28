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
		if(err==FileStatus::CANNOTOPEN)//�޷����ļ�
		{
			QMessageBox box(QMessageBox::Critical, "����", "�޷����ļ���");
			box.exec();
			exit(EXIT_FAILURE);
		}
		if (err == FileStatus::NOTEXIST)//�ļ������ڣ����ȳ��Դ���
		{
			QMessageBox box(QMessageBox::Warning, "����", "����ļ������ڣ������Դ���");
			box.exec();
			try//���Դ���
			{
				CreateFile();
			}
			catch (FileStatus error)
			{
				if (error == FileStatus::CANNOTCREATE)//����ʧ��
				{
					QMessageBox box(QMessageBox::Critical, "����", "�޷���������ļ���");
					box.exec();
					exit(EXIT_FAILURE);
				}
			}
			try//�����ɹ������Դ�
			{
				OpenFile();
			}
			catch (FileStatus error)
			{
				QMessageBox box(QMessageBox::Critical, "����", "�޷����ļ���");
				box.exec();
				exit(EXIT_FAILURE);
			}
			
		}
	}
}
void MainWindow::on_ButtonSale_clicked()
{
	if (manage_window != NULL)//Ϊ�˷�ֹ������ͬʱ�����޸ģ��涨�����͹���������ͬʱ��һ��
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���ȹرչ����ڣ�");
		box.exec();
		return;
	}
	if (sale_window == NULL)//���Ϊ�գ�˵����û�д򿪹�������ڣ���ô���½�һ������ʾ
	{
		
		sale_window = new SaleWindow;
		connect(sale_window, SIGNAL(Close(std::string)), this, SLOT(CloseSon(std::string)));
		sale_window->show();
		
	}
	else//����Ѿ����ˣ��������´�����������ʾԭ����
	{
		sale_window->showNormal();
		sale_window->activateWindow();

	}
}
void MainWindow::on_ButtonManage_clicked()
{
	if (sale_window != NULL)
	{
		QMessageBox box(QMessageBox::Information, "��ʾ", "���ȹر��������ڣ�");
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
	QMessageBox messageBox(QMessageBox::Warning,"����", "��ȷ��Ҫ�˳���?�⽫�ر����е�ǰ�򿪵Ĵ��ڣ�",QMessageBox::Yes | QMessageBox::No, NULL); 
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
