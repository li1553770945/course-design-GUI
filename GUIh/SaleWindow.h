#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
#include "../h/library.h"
class Cart
{
public:
	set<BookData>::iterator book;
	int num;
};
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent = Q_NULLPTR);
signals:
	void Close(std::string);
	void SendBookPtr(const BookData*);

private:
	double sum_money = 0;
	double sum_money_faxed = 0;
	double fax;
	Ui::SaleWindowClass ui;
	void closeEvent(QCloseEvent* event);
	set<BookData>::iterator select_book;//当前选择的书的地址
	vector <Cart> cart;
	bool select;
	void Select(bool);

private slots:
	void on_Confirm_clicked();
	void on_ISBN_returnPressed();
	void on_ButtonDetail_clicked();
	void on_ButtonLibrary_clicked();
	void on_ButtonAddToCart_clicked();
	void on_Num_returnPressed();
	void on_ButtonSattle_clicked();
};

