#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "mainwindowinputfetcher.h"

class QGraphicsView;

namespace Common
{
	class GraphicDrawer;
	class GameState;
}

namespace Ui
{
	class MainWindow;
}

namespace Main
{
class MainWindow : public MainWindowInputFetcher
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

	QGraphicsView& getGraphicsView();

public slots:
	void updateGui(const Common::GameState *gameState);

private:
	Ui::MainWindow *m_ui;
	Common::GraphicDrawer *m_drawer;
};
}

#endif
