#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
#include "../h/library.h"
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent = Q_NULLPTR);
signals:
	void Close(std::string);
	void SendBookPtr(Sale*);

private:
	Ui::SaleWindowClass ui;
	void closeEvent(QCloseEvent* event);
	Sale* book;
private slots:
	void on_Confirm_clicked();
	void on_ISBN_returnPressed();
	void on_ButtonDetail_clicked();
	
};
