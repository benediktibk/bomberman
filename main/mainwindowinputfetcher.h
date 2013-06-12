#ifndef MAIN_MAINWINDOWINPUTFETCHER_H
#define MAIN_MAINWINDOWINPUTFETCHER_H

#include <QMainWindow>
#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include "threading/mutex.h"
#include <vector>
#include <map>

namespace Main
{
class MainWindowInputFetcher :
	public QMainWindow,
	public Common::InputFetcher
{
Q_OBJECT

public:
	MainWindowInputFetcher();
    
    virtual std::map<unsigned int, Common::InputState> getInputStates(std::vector<unsigned int> allPossiblePlayerIds);
	virtual Common::InputState getInputState();

protected:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);

private:
	Common::InputState m_inputState;
    Common::InputState m_inputStatePlayer2;
	Threading::Mutex m_inputStateMutex;
};
}


#endif
