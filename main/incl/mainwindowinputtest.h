#ifndef MAINWINDOWINPUTTEST_H
#define MAINWINDOWINPUTTEST_H

#include "mainwindowinputfetcher.h"

namespace Ui
{
	class MainWindowInputTest;
}

namespace Main
{
class MainWindowInputTest :
		public MainWindowInputFetcher
{
	Q_OBJECT

public:
	MainWindowInputTest();

private:
	Ui::MainWindowInputTest* m_ui;
};
}

#endif
