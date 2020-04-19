#include "../GUIh/MainWindow.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <fstream>
#include <iostream>
#include <io.h>
#include "../h/library.h"
using namespace std;
list<Sale> books;
int main(int argc, char *argv[])
{
	fstream  file;
	if (_access("book.data", 0) == -1)
	{
		file.open("book.data", ios::out);
		file.close();
	}
	file.open("book.data", ios::binary | ios::in | ios::out);
	if (!file.is_open())
	{
		return -1;
	}//读取文件
	while (!file.eof())
	{
		Sale temp;
		file.read((char*)&temp, sizeof(Sale));
		if (file.fail())
			break;
		books.push_back(temp);
	}//读入到books链表
	file.close();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
