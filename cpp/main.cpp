#include "../GUIh/MainWindow.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <fstream>
#include <iostream>
#include <io.h>
#include "../h/library.h"
#include "qmessagebox.h"
#include <qtranslator.h>
using namespace std;
set<BookData> books;
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	MainWindow w;
	QTranslator translator;
	translator.load("qrc/qt_zh_CN");
	a.installTranslator(&translator);
	w.show();
	return a.exec();
}
