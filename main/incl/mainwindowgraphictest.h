#ifndef MAINWINDOWGRAPHICTEST_H
#define MAINWINDOWGRAPHICTEST_H

#include <QMainWindow>

class QGraphicsView;

namespace Ui
{
	class MainWindowGraphicTest;
}

namespace Graphic
{
	class GraphicDrawerQt;
}

namespace Main
{

class MainWindowGraphicTest :
		public QMainWindow
{
	Q_OBJECT

public:
	MainWindowGraphicTest();
	~MainWindowGraphicTest();

private slots:
	void selectGameState(int index);

private:
	void connectSlots();
	void drawState1();

private:
	Ui::MainWindowGraphicTest *m_ui;
	Graphic::GraphicDrawerQt *m_drawer;
};
}

#endif
