#ifndef MAIN_MAINWINDOWCONTROLLER_H
#define MAIN_MAINWINDOWCONTROLLER_H

#include "mainwindowinputfetcher.h"

class QGraphicsView;
class QTimer;

namespace Common
{
	class GraphicDrawer;
	class GameState;
	class GameEngine;
}

namespace Ui
{
	class MainWindow;
}

namespace Main
{
class GameLoop;

class MainWindow :
		public MainWindowInputFetcher
{
	Q_OBJECT

public:
	MainWindow(bool enableOpenGL);
	~MainWindow();

public slots:
	void updateGui(const Common::GameState *gameState);
	void updateFPS();

private:
	const unsigned int m_fpsUpdateTimeStep;
	Ui::MainWindow *m_ui;
	Common::GraphicDrawer *m_drawer;
	Common::GameEngine *m_gameEngine;
	GameLoop *m_gameLoop;
	QTimer *m_timer;
};
}

#endif
