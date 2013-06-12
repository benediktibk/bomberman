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

std::map<unsigned int, InputState> MainWindowInputFetcher::getInputStates(std::vector<unsigned int> allPossiblePlayerIds)
{
    m_inputStateMutex.lock();
    std::map<unsigned int, InputState> stateCopy;
    stateCopy[allPossiblePlayerIds.front()] = m_inputState;
    stateCopy[allPossiblePlayerIds.back()] = m_inputStatePlayer2;
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
	case Key_Left:
		m_inputState.setLeftKeyPressed();
		break;
	case Key_Right:
		m_inputState.setRightKeyPressed();
		break;
	case Key_Space:
		m_inputState.setSpaceKeyPressed();
		break;

    case Key_W:
        m_inputStatePlayer2.setUpKeyPressed();
        break;
    case Key_S:
        m_inputStatePlayer2.setDownKeyPressed();
        break;
    case Key_A:
        m_inputStatePlayer2.setLeftKeyPressed();
        break;
    case Key_D:
        m_inputStatePlayer2.setRightKeyPressed();
        break;
    case Key_Q:
        m_inputStatePlayer2.setSpaceKeyPressed();
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
	case Key_Left:
		m_inputState.setLeftKeyNotPressed();
		break;
	case Key_Right:
		m_inputState.setRightKeyNotPressed();
		break;
	case Key_Space:
		m_inputState.setSpaceKeyNotPressed();
		break;

    case Key_W:
        m_inputStatePlayer2.setUpKeyNotPressed();
        break;
    case Key_S:
        m_inputStatePlayer2.setDownKeyNotPressed();
        break;
    case Key_A:
        m_inputStatePlayer2.setLeftKeyNotPressed();
        break;
    case Key_D:
        m_inputStatePlayer2.setRightKeyNotPressed();
        break;
    case Key_Q:
        m_inputStatePlayer2.setSpaceKeyNotPressed();
        break;

	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
	m_inputStateMutex.unlock();
}

