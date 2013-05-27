#ifndef MAIN_MAINWINDOWINPUTFETCHER_H
#define MAIN_MAINWINDOWINPUTFETCHER_H

#include <QMainWindow>
#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include "threading/mutex.h"

namespace Main
{
class MainWindowInputFetcher :
	public QMainWindow,
	public Common::InputFetcher
{
Q_OBJECT

public:
	MainWindowInputFetcher();

	virtual Common::InputState getInputState();

protected:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

private:
	Common::InputState m_inputState;
	Threading::Mutex m_inputStateMutex;
};
}


#endif
