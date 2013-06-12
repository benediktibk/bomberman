#ifndef MAIN_MAINWINDOW_H
#define MAIN_MAINWINDOW_H

#include "mainwindowinputfetcher.h"
#include "common/leveldefinition.h"
#include "common/graphicdrawer.h"
#include "threading/signal.h"

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
		public MainWindowInputFetcher,
		public Common::GraphicDrawer
{
	Q_OBJECT

public:
	MainWindow(bool enableOpenGL);
	~MainWindow();

	virtual void setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs);
	virtual void draw(const Common::GameState &gameState);

private slots:
	void updateGui(const Common::GameState *gameState);
	void updateStatusBar();

signals:
	void guiUpdateNecessary(const Common::GameState *gameState);

private:
	const unsigned int m_statusBarUpdateTimeStep;
	Ui::MainWindow *m_ui;
	Common::GraphicDrawer *m_drawer;
	Common::LevelDefinition m_level;
	Common::GameEngine *m_gameEngine;
	GameLoop *m_gameLoop;
	QTimer *m_timerStatusBarUpdate;
	Threading::Signal m_guiUpdateFinished;
	bool m_enableOpenGL;
};
}

#endif
