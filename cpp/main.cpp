#include "../GUIh/MainWindow.h"
#include <QtWidgets/QApplication>
#include "../h/library.h"
#include "qmessagebox.h"
#include <qtranslator.h>
#include "QtTest/qtest.h"
using namespace std;
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
