#include "mainwindowinputfetcher.h"
#include <QKeyEvent>

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindowInputFetcher::MainWindowInputFetcher() :
	QMainWindow(0)
{ }

void MainWindowInputFetcher::setAllPossiblePlayerIds(std::vector<unsigned int> allPossiblePlayerIds)
{
    for(size_t i = 0; i < allPossiblePlayerIds.size(); i++)
    {
        m_allPossiblePlayerIds[i] = allPossiblePlayerIds[i];
    }
}

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
	case Key_Left:
		m_inputState.setLeftKeyPressed();
		break;
	case Key_Right:
		m_inputState.setRightKeyPressed();
		break;
	case Key_Space:
		m_inputState.setSpaceKeyPressed();
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
	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
	m_inputStateMutex.unlock();
}

