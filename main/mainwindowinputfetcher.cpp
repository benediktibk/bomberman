#include "main/mainwindowinputfetcher.h"
#include "threading/lock.h"
#include <QKeyEvent>
#include <assert.h>

using namespace Common;
using namespace Main;
using namespace Threading;
using namespace Qt;
using namespace std;

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
	Lock lock(m_inputStateMutex);
	map<unsigned int, InputState> stateCopy;
	stateCopy[m_playerIds.front()] = m_inputStatePlayerOne;

	if (m_playerIds.size() > 1)
		stateCopy[m_playerIds.back()] = m_inputStatePlayerTwo;

	return stateCopy;
}

void MainWindowInputFetcher::keyPressEvent(QKeyEvent *event)
{
	Lock lock(m_inputStateMutex);
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

	case Key_P:
		emit pauseButtonPressed();
		break;
	case Key_M:
		emit muteButtonPressed();
		break;

	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
}

void MainWindowInputFetcher::keyReleaseEvent(QKeyEvent *event)
{
	Lock lock(m_inputStateMutex);
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
}

