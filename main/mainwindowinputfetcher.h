#ifndef MAIN_MAINWINDOWINPUTFETCHER_H
#define MAIN_MAINWINDOWINPUTFETCHER_H

#include <QMainWindow>
#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include "threading/mutex.h"
#include <vector>
#include <map>

namespace Main
{
	class MainWindowInputFetcher :
		public QMainWindow,
		public Common::InputFetcher
	{
	Q_OBJECT

	public:
		MainWindowInputFetcher();

		virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &allPossiblePlayerIds);
		virtual std::map<unsigned int, Common::InputState> getInputStates();

	signals:
		void pauseButtonPressed();
		void muteButtonPressed();

	protected:
		virtual void keyPressEvent(QKeyEvent *event);
		virtual void keyReleaseEvent(QKeyEvent *event);

	private:
		Common::InputState m_inputStatePlayerOne;
		Common::InputState m_inputStatePlayerTwo;
		Threading::Mutex m_inputStateMutex;
		std::vector<unsigned int> m_playerIds;
	};
}

#endif
