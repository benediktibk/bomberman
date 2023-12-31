#include <QApplication>
#include <QtCore/QStringList>
#include "main/gamewindow.h"
#include "main/startwindow.h"
#include "main/splashscreen.h"

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

	SplashScreen splashScreen;
	GameWindow gameWindow;
	StartWindow startWindow(enableOpenGL);
	QObject::connect(	&startWindow, SIGNAL(startGameSignal(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool, double)),
						&gameWindow, SLOT(startGame(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool, double)));
	QObject::connect(	&gameWindow, SIGNAL(levelBuildingNotCorectSignal()),
						&startWindow, SLOT(levelBuildingNotCorrect()));
	QObject::connect(	&gameWindow, SIGNAL(setSoundSettingsSignal(bool, int)),
						&startWindow, SLOT(setSoundSettings(bool, int)));
	QObject::connect(	&gameWindow, SIGNAL(winnerOfGameSignal(int)),
						&startWindow, SLOT(winnerOfGame(int)));
	QObject::connect(	&splashScreen, SIGNAL(closed()),
						&startWindow, SLOT(show()));
	splashScreen.show();
	return application.exec();
}
