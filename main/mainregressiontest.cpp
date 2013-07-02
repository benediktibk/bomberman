#include "main/mainwindow.h"
#include "main/userinputsimulator.h"
#include <QApplication>
#include <QtCore/QObject>

int main(int argc, char **argv)
{
	QApplication application(argc, argv);

	Main::MainWindow mainWindow;
	Main::UserInputSimulator userInputSimulator;
	QObject::connect(	&userInputSimulator, SIGNAL(startGame(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool)),
						&mainWindow, SLOT(startGame(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool)));
	QObject::connect(	&userInputSimulator, SIGNAL(closeGame()),
						&mainWindow, SLOT(closeGame()));
	QObject::connect(	&mainWindow, SIGNAL(winnerOfGameSignal(const char*)),
						&userInputSimulator, SLOT(winnerOfGame(const char*)));
	mainWindow.show();
	return application.exec();
}

