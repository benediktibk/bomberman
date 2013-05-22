#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QGraphicsScene>
#include "mainwindowinputfetcher.h"

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
	MainWindow(QGraphicsScene &scene);

private:
	Ui::MainWindow* m_ui;
};
}

#endif
