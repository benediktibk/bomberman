#ifndef MAIN_USERINPUTSIMULATOR_H
#define MAIN_USERINPUTSIMULATOR_H

#include "main/gamewindow.h"
#include "common/randomdecision.h"
#include "gameengine/computerenemylevel.h"

class QTimer;

namespace Common
{
	class RandomDecision;
}

namespace Main
{
	class UserInputSimulator :
			public GameWindow
	{
		Q_OBJECT

	public:
		UserInputSimulator();
		virtual ~UserInputSimulator();

	public:
		virtual double draw(const Common::GameState &gameState);

	public slots:
		void winnerOfGame(int winner);
		void restartGame();

	private:
		QTimer *m_timerForRestart;
		const unsigned int m_maximumTimeToRunInMsec;
		Common::RandomDecision *m_enableOpenGL;
	};
}

#endif
