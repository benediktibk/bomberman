#include <QApplication>
#include "mainwindow.h"
#include "gameloop.h"
#include "graphicdrawerqt.h"
#include "gameengineimpl.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	MainWindow mainWindow;
	GameEngine::GameEngineImpl gameEngine;
	GameLoop gameLoop(mainWindow, gameEngine);

	mainWindow.show();
	QObject::connect(	&gameLoop, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
						&mainWindow, SLOT(updateGui(const Common::GameState*)));
	int result = a.exec();

	gameLoop.stop();
	return result;
}