#include "main/userinputsimulator.h"
#include <QtCore/QTimer>
#include <stdlib.h>

using namespace Main;
using namespace Common;

UserInputSimulator::UserInputSimulator() :
	m_timerForRestart(new QTimer()),
	m_timerForPossibleClose(new QTimer()),
	m_maximumTimeToRunInMsec(120*1000),
	m_timeTillPossibleCloseGameInMsec(5*1000),
	m_closeGame(new RandomDecision(0.1)),
	m_enableOpenGL(new RandomDecision(0.5))
{
	connect(m_timerForRestart, SIGNAL(timeout()), this, SLOT(restartGame()));
	connect(m_timerForPossibleClose, SIGNAL(timeout()), this, SLOT(possibleCloseGame()));
	m_timerForRestart->start(rand()%m_maximumTimeToRunInMsec);
	m_timerForPossibleClose->start(m_timeTillPossibleCloseGameInMsec);
}

UserInputSimulator::~UserInputSimulator()
{
	delete m_timerForRestart;
	delete m_timerForPossibleClose;
	delete m_closeGame;
	delete m_enableOpenGL;
}

void UserInputSimulator::restartGame()
{
	unsigned int humanPlayerCount = 2;
	bool enableOpenGL = m_enableOpenGL->decide();
	unsigned int computerEnemyCount = rand()%99;
	emit startGame(enableOpenGL, "World At War", humanPlayerCount, computerEnemyCount, GameEngine::ComputerEnemyLevelHard, true);
	m_timerForRestart->start(rand()%m_maximumTimeToRunInMsec);
}

void UserInputSimulator::possibleCloseGame()
{
	if (m_closeGame->decide())
		emit closeGame();
	m_timerForPossibleClose->start(m_timeTillPossibleCloseGameInMsec);
}


void UserInputSimulator::winnerOfGame(const char *)
{
	restartGame();
}
