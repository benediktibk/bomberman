#include <QApplication>
#include <QtCore/QStringList>
#include "mainwindow.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	QStringList arguments = QCoreApplication::arguments();
	bool enableOpenGL;

	if (arguments.contains("--enableOpenGL", Qt::CaseSensitive))
		enableOpenGL = true;
	else
		enableOpenGL = false;

	MainWindow mainWindow(enableOpenGL);
	mainWindow.show();
	return application.exec();
}