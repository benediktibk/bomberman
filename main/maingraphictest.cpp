#include <QApplication>
#include "main/graphictestwindow.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	GraphicTestWindow mainWindow;
	mainWindow.show();
	return a.exec();
}
