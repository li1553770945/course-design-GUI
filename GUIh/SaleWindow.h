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
	void SendBookPtr(const BookData*);

private:
	Ui::SaleWindowClass ui;
	void closeEvent(QCloseEvent* event);
	const BookData* book;
private slots:
	void on_Confirm_clicked();
	void on_ISBN_returnPressed();
	void on_ButtonDetail_clicked();
	void on_ButtonLibrary_clicked();
	
};
