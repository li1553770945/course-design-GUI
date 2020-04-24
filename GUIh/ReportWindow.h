#pragma once
#include "ui_ReportWindow.h"
class ReportWindow : public QMainWindow
{
	Q_OBJECT

public:
	ReportWindow(QWidget* parent = Q_NULLPTR);


private:
	Ui::ReportWindowClass ui;
	void closeEvent(QCloseEvent* event);
	void SetData();
private slots:
	void on_CheckBoxName_clicked();
	void on_CheckBoxISBN_clicked();
	void on_CheckBoxAuthor_clicked();
	void on_CheckBoxPublisher_clicked();
	void on_CheckBoxDateAdded_clicked();
	void on_CheckBoxQty_clicked();
	void on_CheckBoxRetail_clicked();
	void on_CheckBoxWholesale_clicked();
	void on_ButtonFlush_clicked();
signals:
	void Close(std::string);
};

