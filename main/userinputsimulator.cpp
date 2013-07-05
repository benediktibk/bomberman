#include "main/userinputsimulator.h"
#include <QtCore/QTimer>
#include <stdlib.h>
#include <iostream>

using namespace Main;
using namespace Common;
using namespace std;

UserInputSimulator::UserInputSimulator() :
	m_timerForRestart(new QTimer()),
	m_maximumTimeToRunInMsec(120*1000),
	m_enableOpenGL(new RandomDecision(0.5))
{
	connect(	m_timerForRestart, SIGNAL(timeout()),
				this, SLOT(restartGame()));
	connect(	this, SIGNAL(winnerOfGameSignal(int)),
				this, SLOT(winnerOfGame(int)));
	restartGame();
}

UserInputSimulator::~UserInputSimulator()
{
	delete m_timerForRestart;
	delete m_enableOpenGL;
}

double UserInputSimulator::draw(const GameState &gameState)
{
	cout << "redraw requested";
	double result = GameWindow::draw(gameState);
	cout << " - redraw finished" << endl;
	return result;
}

void UserInputSimulator::restartGame()
{
	cout << "restarting the game" << endl;
	unsigned int humanPlayerCount = rand()%2 + 1;
	bool enableOpenGL = m_enableOpenGL->decide();
	unsigned int computerEnemyCount = rand()%99;
	startGame(enableOpenGL, "world_at_war", humanPlayerCount, computerEnemyCount, GameEngine::ComputerEnemyLevelHard, true, 0.75);
	m_timerForRestart->start(rand()%m_maximumTimeToRunInMsec);
	show();
}

void UserInputSimulator::winnerOfGame(int)
{
	cout << "game has finished by itself" << endl;
	restartGame();
}
