#include "../GUIh/ReportWindow.h"
ReportWindow::ReportWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}
void ReportWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("report"));
}