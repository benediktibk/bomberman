#include <QApplication>
#include "mainwindow.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
	return application.exec();
}