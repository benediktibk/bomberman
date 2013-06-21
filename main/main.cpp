#include <QApplication>
#include <QtCore/QStringList>
#include "mainwindow.h"
#include "startwindow.h"

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

	MainWindow mainWindow;
	StartWindow startWindow(enableOpenGL);
	QObject::connect(	&startWindow, SIGNAL(startGameSignal(bool,const char*)),
						&mainWindow, SLOT(startGame(bool,const char*)));
	startWindow.show();
	return application.exec();
}
