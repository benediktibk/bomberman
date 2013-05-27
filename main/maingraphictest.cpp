#include <QApplication>
#include "mainwindowgraphictest.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	MainWindowGraphicTest mainWindow;
	mainWindow.show();
	return a.exec();
}
