#pragma once
#include "ui_BookInfoWindow.h"
#include "../h/library.h"
class BookInfoWindow : public QMainWindow
{
	Q_OBJECT

public:
	BookInfoWindow(QWidget* parent = Q_NULLPTR);
	void Set();
private slots:
	void ReceiveBookPtr(Sale*);
private:
	Ui::BookInfoWindowClass ui;
	Sale* book;
};