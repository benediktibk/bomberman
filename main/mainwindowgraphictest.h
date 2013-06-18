#ifndef MAIN_MAINWINDOWGRAPHICTEST_H
#define MAIN_MAINWINDOWGRAPHICTEST_H

#include <QMainWindow>

class QGraphicsView;

namespace Common
{
	class GameState;
}

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
		void drawState2();
		void drawState3();
		void drawState4();
		void drawState(const Common::GameState &game);

	private:
		Ui::MainWindowGraphicTest *m_ui;
		Graphic::GraphicDrawerQt *m_drawer;
	};
}

#endif
