#ifndef MAIN_GAMEWINDOW_H
#define MAIN_GAMEWINDOW_H

#include "main/inputfetcherwindow.h"
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
	class GameWindow;
}

namespace Main
{
	class GameLoop;

	class GameWindow :
			public InputFetcherWindow,
			public Common::GraphicDrawer
	{
		Q_OBJECT

	public:
		GameWindow();
		~GameWindow();

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
		void volumeChanged();

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
		bool createLevel(const std::string &levelName);
		void createGameLoop();
		void createDrawer(bool enableOpenGL);
		void createSoundPlayer(bool mute);
		void createGameEngine(unsigned int humanPlayerCount, unsigned int computerEnemyCount);
		void createAllPlayerInputFetcher(GameEngine::ComputerEnemyLevel computerEnemyLevel);
		void freeMemory();
		virtual void closeEvent(QCloseEvent *);

	private:
		const unsigned int m_statusBarUpdateTimeStep;
		Ui::GameWindow *m_ui;
		Common::GraphicDrawer *m_drawer;
		Common::LevelDefinition *m_level;
		Common::GameEngine *m_gameEngine;
		Sound::SoundPlayer *m_soundPlayer;
		GameLoop *m_gameLoop;
		InputFetcher *m_allPlayerInputFetcher;
		QTimer *m_timerUserInfoUpdate;
		Threading::Signal m_guiUpdateFinished;
		bool m_gameRunning;
		Threading::Mutex m_gameRunningMutex;
		Threading::Signal m_drawFinished;
	};
}

#endif
