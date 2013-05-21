#include <QApplication>
#include "mainwindow.h"
#include "gameloop.h"
#include "graphicdrawerqt.h"
#include "gameengineimpl.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	Graphic::GraphicDrawerQt graphicDrawer;
	GameEngine::GameEngineImpl gameEngine;
	MainWindow mainWindow(graphicDrawer.getScene());
	GameLoop gameLoop(mainWindow, gameEngine, graphicDrawer);

	mainWindow.show();
	int result = a.exec();
	gameLoop.waitTillFinished();

	return result;
}