#include "../GUIh/FindWindow.h"
FindWindow::FindWindow(QWidget* parent) :QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}
void FindWindow::closeEvent(QCloseEvent* event)
{
	emit Close(std::string("find"));
}