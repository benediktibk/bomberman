#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "mainwindowinputfetcher.h"

class QGraphicsView;

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

	QGraphicsView& getGraphicsView();

private:
	Ui::MainWindow* m_ui;
};
}

#endif
