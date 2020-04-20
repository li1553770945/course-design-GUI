#include "../GUIh/MainWindow.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <fstream>
#include <iostream>
#include <io.h>
#include "../h/library.h"
#include "qmessagebox.h"
using namespace std;
list<Sale> books;
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
