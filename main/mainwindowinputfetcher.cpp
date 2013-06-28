#include "mainwindowinputfetcher.h"
#include <QKeyEvent>
#include <assert.h>

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindowInputFetcher::MainWindowInputFetcher() :
	QMainWindow(0)
{ }

void MainWindowInputFetcher::setAllPossiblePlayerIDs(const std::vector<unsigned int> &allPossiblePlayerIds)
{
	assert(allPossiblePlayerIds.size() > 0 && allPossiblePlayerIds.size() < 3);
	m_playerIds = allPossiblePlayerIds;
}

std::map<unsigned int, InputState> MainWindowInputFetcher::getInputStates()
{
	m_inputStateMutex.lock();
	std::map<unsigned int, InputState> stateCopy;
	stateCopy[m_playerIds.front()] = m_inputStatePlayerOne;
	stateCopy[m_playerIds.back()] = m_inputStatePlayerTwo;
	m_inputStateMutex.unlock();
	return stateCopy;
}

void MainWindowInputFetcher::keyPressEvent(QKeyEvent *event)
{
	m_inputStateMutex.lock();
	switch (event->key())
	{
	case Key_Up:
		m_inputStatePlayerOne.setUpKeyPressed();
		break;
	case Key_Down:
		m_inputStatePlayerOne.setDownKeyPressed();
		break;
	case Key_Left:
		m_inputStatePlayerOne.setLeftKeyPressed();
		break;
	case Key_Right:
		m_inputStatePlayerOne.setRightKeyPressed();
		break;
	case Key_Space:
		m_inputStatePlayerOne.setSpaceKeyPressed();
		break;

	case Key_W:
		m_inputStatePlayerTwo.setUpKeyPressed();
		break;
	case Key_S:
		m_inputStatePlayerTwo.setDownKeyPressed();
		break;
	case Key_A:
		m_inputStatePlayerTwo.setLeftKeyPressed();
		break;
	case Key_D:
		m_inputStatePlayerTwo.setRightKeyPressed();
		break;
	case Key_Q:
		m_inputStatePlayerTwo.setSpaceKeyPressed();
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
		m_inputStatePlayerOne.setUpKeyNotPressed();
		break;
	case Key_Down:
		m_inputStatePlayerOne.setDownKeyNotPressed();
		break;
	case Key_Left:
		m_inputStatePlayerOne.setLeftKeyNotPressed();
		break;
	case Key_Right:
		m_inputStatePlayerOne.setRightKeyNotPressed();
		break;
	case Key_Space:
		m_inputStatePlayerOne.setSpaceKeyNotPressed();
		break;

	case Key_W:
		m_inputStatePlayerTwo.setUpKeyNotPressed();
		break;
	case Key_S:
		m_inputStatePlayerTwo.setDownKeyNotPressed();
		break;
	case Key_A:
		m_inputStatePlayerTwo.setLeftKeyNotPressed();
		break;
	case Key_D:
		m_inputStatePlayerTwo.setRightKeyNotPressed();
		break;
	case Key_Q:
		m_inputStatePlayerTwo.setSpaceKeyNotPressed();
		break;

	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
	m_inputStateMutex.unlock();
}

