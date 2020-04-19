#pragma once
#include "ui_BookInfoWindow.h"
class BookInfoWindow : public QMainWindow
{
	Q_OBJECT

public:
	BookInfoWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::BookInfoWindowClass ui;
};