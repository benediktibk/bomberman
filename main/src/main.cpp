#include <QApplication>
#include "mainwindow.h"
#include "gameloop.h"
#include "graphicdrawerqt.h"
#include "gameengineimpl.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	GameEngine::GameEngineImpl gameEngine;
	MainWindow mainWindow;
	GameLoop gameLoop(mainWindow, gameEngine);
	mainWindow.setSignalGuiUpdateFinished(gameLoop.getSignalGuiUpdateFinished());

	mainWindow.show();
	QObject::connect(	&gameLoop, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
						&mainWindow, SLOT(updateGui(const Common::GameState*)));
	int result = a.exec();

	gameLoop.stop();
	return result;
}