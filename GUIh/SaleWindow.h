#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SaleWindow.h"
class SaleWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaleWindow(QWidget* parent = Q_NULLPTR);
signals:
	void Close(std::string);

private:
	Ui::SaleWindowClass ui;
	void closeEvent(QCloseEvent* event);
private slots:
	void on_Confirm_clicked();
	void on_ISBN_returnPressed();
};
