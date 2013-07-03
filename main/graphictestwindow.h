#ifndef MAIN_GRAPHICTESTWINDOW_H
#define MAIN_GRAPHICTESTWINDOW_H

#include <QMainWindow>

class QGraphicsView;

namespace Common
{
	class GameState;
}

namespace Ui
{
	class GraphicTestWindow;
}

namespace Graphic
{
	class GraphicDrawerQt;
}

namespace Main
{
	class GraphicTestWindow :
			public QMainWindow
	{
		Q_OBJECT

	public:
		GraphicTestWindow();
		~GraphicTestWindow();

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
		Ui::GraphicTestWindow *m_ui;
		Graphic::GraphicDrawerQt *m_drawer;
	};
}

#endif
