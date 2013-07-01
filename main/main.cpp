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
	QObject::connect(	&startWindow, SIGNAL(startGameSignal(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool)),
						&mainWindow, SLOT(startGame(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool)));
	QObject::connect(	&startWindow, SIGNAL(closeGameSignal()),
						&mainWindow, SLOT(closeGame()));
	QObject::connect(	&mainWindow, SIGNAL(levelBuildingNotCorectSignal()),
						&startWindow, SLOT(levelBuildingNotCorrect()));
	QObject::connect(	&mainWindow, SIGNAL(closeGameSignal()),
						&startWindow, SLOT(closeGameClicked()));
	QObject::connect(	&mainWindow, SIGNAL(winnerOfGameSignal(const char*)),
						&startWindow, SLOT(winnerOfGame(const char*)));
	startWindow.show();
	return application.exec();
}
