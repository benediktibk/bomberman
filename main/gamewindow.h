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
	class StopWatch;
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
		virtual double draw(const Common::GameState &gameState);
		bool eventFilter(QObject *obj, QEvent *event);

	public slots:
		void startGame(bool enableOpenGL, const char* levelname,
				unsigned int humanPlayerCount, unsigned int computerEnemyCount,
				GameEngine::ComputerEnemyLevel computerEnemyLevel, bool mute, double volume);

	private slots:
		void updateGraphicScene(const Common::GameState *gameState);
		void updateViewPorts();
		void updateStatusInformation();
		void pauseButtonPushed();
		void muteButtonPushed();
		void winnerOfGame(int winner);
		void volumeChanged();
		void closeGame();

	signals:
		void guiUpdateNecessary(const Common::GameState *gameState);
		void levelBuildingNotCorectSignal();
		void closeGameSignal(bool oldMute, int oldVolume);
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
		void createSoundPlayer(bool mute, double volume);
		void createGameEngine(unsigned int humanPlayerCount, unsigned int computerEnemyCount);
		void createAllPlayerInputFetcher(GameEngine::ComputerEnemyLevel computerEnemyLevel);
		void createViews(unsigned int humanPlayerCount);
		QGraphicsView* createView();
		void freeMemory();
		virtual void closeEvent(QCloseEvent *);

	private:
		const double m_statusBarUpdateTimeStep;
		Ui::GameWindow *m_ui;
		Common::GraphicDrawer *m_drawer;
		Common::LevelDefinition *m_level;
		Common::GameEngine *m_gameEngine;
		Sound::SoundPlayer *m_soundPlayer;
		GameLoop *m_gameLoop;
		InputFetcher *m_allPlayerInputFetcher;
		QTimer *m_timerStatusInformationUpdate;
		QTimer *m_timerUpdateViewPorts;
		Threading::Signal m_guiUpdateFinished;
		bool m_gameRunning;
		Threading::Mutex m_gameRunningMutex;
		Threading::Signal m_drawFinished;
		QGraphicsView *m_viewOne;
		QGraphicsView *m_viewTwo;
		std::vector<QGraphicsView*> m_viewsAsVector;
		Common::StopWatch *m_framesPerSecondWatch;
		Common::StopWatch *m_waitingForUpdateSignalWatch;
		double m_timeForViewPortUpdates;
		double m_timeSpentOnDrawing;
		double m_timeSpentOnWaitingForUpdateSignal;
	};
}

#endif
