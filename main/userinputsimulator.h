#ifndef MAIN_USERINPUTSIMULATOR_H
#define MAIN_USERINPUTSIMULATOR_H

#include "main/mainwindow.h"
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
			public MainWindow
	{
		Q_OBJECT

	public:
		UserInputSimulator();
		virtual ~UserInputSimulator();

	public slots:
		void winnerOfGame(const char *winner);
		void restartGame();

	private:
		QTimer *m_timerForRestart;
		const unsigned int m_maximumTimeToRunInMsec;
		Common::RandomDecision *m_enableOpenGL;
	};
}

#endif
