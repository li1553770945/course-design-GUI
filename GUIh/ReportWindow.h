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
signals:
	void Close(std::string);
};

