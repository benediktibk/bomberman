#ifndef MAIN_USERINPUTSIMULATOR_H
#define MAIN_USERINPUTSIMULATOR_H

#include <QtCore/QObject>
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
			public QObject
	{
		Q_OBJECT

	public:
		UserInputSimulator();
		virtual ~UserInputSimulator();

	signals:
		void startGame(bool, const char*, unsigned int, unsigned int, GameEngine::ComputerEnemyLevel, bool);
		void closeGame();

	public slots:
		void winnerOfGame(const char *winner);
		void restartGame();
		void possibleCloseGame();

	private:
		QTimer *m_timerForRestart;
		QTimer *m_timerForPossibleClose;
		const unsigned int m_maximumTimeToRunInMsec;
		const unsigned int m_timeTillPossibleCloseGameInMsec;
		Common::RandomDecision *m_closeGame;
		Common::RandomDecision *m_enableOpenGL;
	};
}

#endif
