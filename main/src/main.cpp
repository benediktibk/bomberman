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
	Graphic::GraphicDrawerQt graphicDrawer(mainWindow.getGraphicsView());
	GameEngine::GameEngineImpl gameEngine;
	GameLoop gameLoop(mainWindow, gameEngine, graphicDrawer);

	mainWindow.show();
	int result = a.exec();
	gameLoop.waitTillFinished();

	return result;
}