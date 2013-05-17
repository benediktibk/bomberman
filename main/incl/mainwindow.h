#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QMainWindow>

namespace Ui
{
	class MainWindow;
}

class MainWindow :
		public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:

private:
	void connectButtons();

private:
	Ui::MainWindow* m_ui;
};

#endif
