#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ManageWindow.h"
#include "../h/library.h"
class ManageWindow : public QMainWindow
{
	Q_OBJECT

public:
	ManageWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::ManageWindowClass ui;
	void closeEvent(QCloseEvent* event);
	set<BookData>::iterator  current_edit_book;
private slots:
	void on_ButtonAdd_clicked();
	void on_ButtonISBNConfirm_clicked();
	void on_ButtonSave_clicked();
	void on_ButtonDelete_clicked();//TODO:����������ʵ��
	void on_ISBNInput_returnPressed();
	
signals:
	void Close(std::string);
	
};
