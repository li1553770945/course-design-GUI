#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ManageWindow.h"
class ManageWindow : public QMainWindow
{
	Q_OBJECT

public:
	ManageWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::ManageWindowClass ui;
	void closeEvent(QCloseEvent* event);
private slots:
	void on_ButtonAdd_clicked();
signals:
	void Close(std::string);
	
};
