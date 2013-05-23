#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "mainwindowinputfetcher.h"

class QGraphicsView;

namespace Common
{
	class GraphicDrawer;
	class GameState;
}

namespace Threading
{
	class Signal;
}

namespace Ui
{
	class MainWindow;
}

namespace Main
{
class MainWindow :
		public MainWindowInputFetcher
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

	QGraphicsView& getGraphicsView();
	void setSignalGuiUpdateFinished(Threading::Signal &signal);

public slots:
	void updateGui(const Common::GameState *gameState);

private:
	Ui::MainWindow *m_ui;
	Common::GraphicDrawer *m_drawer;
	Threading::Signal *m_signalGuiUpdateFinished;
};
}

#endif
