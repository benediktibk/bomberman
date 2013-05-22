#ifndef MAINWINDOWINPUTFETCHER_H
#define MAINWINDOWINPUTFETCHER_H

#include <QMainWindow>
#include "inputfetcher.h"
#include "inputstate.h"
#include "mutex.h"

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

private slots:

private:
    Common::InputState m_inputState;
    Threading::Mutex m_inputStateMutex;
};
}


#endif
