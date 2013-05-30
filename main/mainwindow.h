#ifndef MAIN_MAINWINDOW_H
#define MAIN_MAINWINDOW_H

#include "mainwindowinputfetcher.h"
#include "common/leveldefinition.h"

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
    Common::LevelDefinition m_level;
	Common::GameEngine *m_gameEngine;
	GameLoop *m_gameLoop;
	QTimer *m_timer;
};
}

#endif
