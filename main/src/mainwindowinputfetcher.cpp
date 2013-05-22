#include "mainwindowinputfetcher.h"
#include <QKeyEvent>

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindowInputFetcher::MainWindowInputFetcher() :
    QMainWindow(0)
{ }

InputState MainWindowInputFetcher::getInputState()
{
    m_inputStateMutex.lock();
    InputState stateCopy = m_inputState;
    m_inputStateMutex.unlock();
    return stateCopy;
}

void MainWindowInputFetcher::keyPressEvent(QKeyEvent *event)
{
    m_inputStateMutex.lock();
    switch (event->key())
    {
    case Key_Up:
        m_inputState.setUpKeyPressed();
        break;
    case Key_Down:
        m_inputState.setDownKeyPressed();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
    m_inputStateMutex.unlock();
}

void MainWindowInputFetcher::keyReleaseEvent(QKeyEvent *event)
{
    m_inputStateMutex.lock();
    switch (event->key())
    {
    case Key_Up:
        m_inputState.setUpKeyNotPressed();
        break;
    case Key_Down:
        m_inputState.setDownKeyNotPressed();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
    m_inputStateMutex.unlock();
}

