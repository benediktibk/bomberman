#include "main/userinputsimulator.h"
#include <QtCore/QTimer>
#include <stdlib.h>

using namespace Main;
using namespace Common;

UserInputSimulator::UserInputSimulator() :
	m_timerForRestart(new QTimer()),
	m_maximumTimeToRunInMsec(120*1000),
	m_enableOpenGL(new RandomDecision(0.5))
{
	connect(	m_timerForRestart, SIGNAL(timeout()),
				this, SLOT(restartGame()));
	connect(	this, SIGNAL(winnerOfGameSignal(const char*)),
				this, SLOT(winnerOfGame(const char*)));
	restartGame();
}

UserInputSimulator::~UserInputSimulator()
{
	delete m_timerForRestart;
	delete m_enableOpenGL;
}

void UserInputSimulator::restartGame()
{
	unsigned int humanPlayerCount = rand()%2 + 1;
	bool enableOpenGL = m_enableOpenGL->decide();
	unsigned int computerEnemyCount = rand()%99;
	startGame(enableOpenGL, "world_at_war", humanPlayerCount, computerEnemyCount, GameEngine::ComputerEnemyLevelHard, true);
	m_timerForRestart->start(rand()%m_maximumTimeToRunInMsec);
	show();
}

void UserInputSimulator::winnerOfGame(const char *)
{
	restartGame();
}
