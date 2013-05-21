#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "inputfetcher.h"
#include "inputstate.h"
#include "mutex.h"

namespace Ui
{
	class MainWindow;
}

namespace Main
{
class MainWindow :
		public QMainWindow,
		public Common::InputFetcher
{
	Q_OBJECT

public:
	MainWindow(QGraphicsScene &scene);

	virtual Common::InputState getInputState();

protected:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

private slots:

private:
	Ui::MainWindow* m_ui;
	Common::InputState m_inputState;
	Threading::Mutex m_inputStateMutex;
};
}

#endif
