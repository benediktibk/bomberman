#ifndef MAINWINDOWINPUTTEST_H
#define MAINWINDOWINPUTTEST_H

#include "mainwindowinputfetcher.h"

namespace Ui
{
	class MainWindowInputTest;
}

class QTimer;

namespace Main
{
class MainWindowInputTest :
		public MainWindowInputFetcher
{
	Q_OBJECT

public:
	MainWindowInputTest();

private slots:
    void inputStateCalled();

private:
    void connectButtons();

private:
	Ui::MainWindowInputTest* m_ui;
    QTimer *m_timer;
};
}

#endif
