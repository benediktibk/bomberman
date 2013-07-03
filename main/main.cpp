#include <QApplication>
#include <QtCore/QStringList>
#include "gamewindow.h"
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

	GameWindow gameWindow;
	StartWindow startWindow(enableOpenGL);
	QObject::connect(	&startWindow, SIGNAL(startGameSignal(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool)),
						&gameWindow, SLOT(startGame(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool)));
	QObject::connect(	&startWindow, SIGNAL(closeGameSignal()),
						&gameWindow, SLOT(closeGame()));
	QObject::connect(	&gameWindow, SIGNAL(levelBuildingNotCorectSignal()),
						&startWindow, SLOT(levelBuildingNotCorrect()));
	QObject::connect(	&gameWindow, SIGNAL(closeGameSignal()),
						&startWindow, SLOT(closeGameClicked()));
	QObject::connect(	&gameWindow, SIGNAL(winnerOfGameSignal(int)),
						&startWindow, SLOT(winnerOfGame(int)));
	startWindow.show();
	return application.exec();
}
