#pragma once
#include <QtWidgets/QMainWindow>
#include <ui_FindWindow.h>
class FindWindow : public QMainWindow
{
	Q_OBJECT

public:
	FindWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::FindWindowClass ui;
	void closeEvent(QCloseEvent* event);
signals:
	void Close(std::string);
};