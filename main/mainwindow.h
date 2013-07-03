#ifndef MAIN_MAINWINDOW_H
#define MAIN_MAINWINDOW_H

#include "main/mainwindowinputfetcher.h"
#include "common/leveldefinition.h"
#include "common/graphicdrawer.h"
#include "threading/signal.h"
#include "threading/mutex.h"
#include "gameengine/computerenemylevel.h"

class QGraphicsView;
class QTimer;

namespace Common
{
	class GraphicDrawer;
	class GameState;
	class GameEngine;
}

namespace Sound
{
	class SoundPlayer;
}

namespace Ui
{
	class MainWindow;
}

namespace Main
{
	class GameLoop;

	class MainWindow :
			public MainWindowInputFetcher,
			public Common::GraphicDrawer
	{
		Q_OBJECT

	public:
		MainWindow();
		~MainWindow();

		virtual void setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs);
		virtual void draw(const Common::GameState &gameState);

	public slots:
		void startGame(
				bool enableOpenGL, const char* levelname,
				unsigned int humanPlayerCount, unsigned int computerEnemyCount,
				GameEngine::ComputerEnemyLevel computerEnemyLevel, bool mute);
		void closeGame();

	private slots:
		void updateGui(const Common::GameState *gameState);
		void updateUserInfo();
		void pauseButtonPushed();
		void muteButtonPushed();
		void winnerOfGame(int winner);

	signals:
		void guiUpdateNecessary(const Common::GameState *gameState);
		void levelBuildingNotCorectSignal();
		void closeGameSignal();
		void winnerOfGameSignal(int winner);

	private:
		void finishGame();
		void updateStatusBar();
		void updatePlayerStateInfo();
		void updateMuteButtonLabel();
		void updatePauseButtonLabel();

		virtual void closeEvent(QCloseEvent *);

	private:
		const unsigned int m_statusBarUpdateTimeStep;
		Ui::MainWindow *m_ui;
		Common::GraphicDrawer *m_drawer;
		Common::LevelDefinition *m_level;
		Common::GameEngine *m_gameEngine;
		Sound::SoundPlayer *m_soundPlayer;
		GameLoop *m_gameLoop;
		InputFetcher *m_allPlayerInputFetcher;
		QTimer *m_timerUserInfoUpdate;
		Threading::Signal m_guiUpdateFinished;
		bool m_enableOpenGL;
		bool m_gameStarted;
		Threading::Mutex m_gameStartMutex;
		bool m_gameFinished;
		Threading::Mutex m_gameFinishedMutex;
	};
}

#endif
