#include "main/mainwindow.h"
#include "main/gameloop.h"
#include "ui_mainwindow.h"
#include "graphic/graphicdrawerqt.h"
#include "common/gamestate.h"
#include "gameengine/gameengineimpl.h"
#include "sound/soundplayer.h"
#include "threading/lock.h"
#include <assert.h>
#include <QtCore/QTimer>
#include <QScrollBar>

using namespace Main;
using namespace Graphic;
using namespace Threading;
using namespace std;

MainWindow::MainWindow() :
	m_statusBarUpdateTimeStep(250),
	m_ui(new Ui::MainWindow),
	m_drawer(0),
	m_level(0),
	m_gameEngine(0),
	m_soundPlayer(0),
	m_gameLoop(0),
	m_timerUserInfoUpdate(new QTimer(this)),
	m_gameStarted(false),
	m_gameFinished(false)
{
	m_ui->setupUi(this);

	connect(	this, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	connect(	m_timerUserInfoUpdate, SIGNAL(timeout()),
				this, SLOT(updateUserInfo()));
	connect(	m_ui->pauseButton, SIGNAL(clicked()),
				this, SLOT(pauseButtonPushed()));
	connect(	m_ui->muteButton, SIGNAL(clicked()),
				this, SLOT(muteButtonPushed()));
	connect(	this, SIGNAL(pauseButtonPressed()),
				this, SLOT(pauseButtonPushed()));
	connect(	this, SIGNAL(muteButtonPressed()),
				this, SLOT(muteButtonPushed()));
}

MainWindow::~MainWindow()
{
	m_guiUpdateFinished.send();
	finishGame();
	delete m_ui;
}

void MainWindow::setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs)
{
	m_drawer->setResponsibleForPlayers(playerIDs);
}

void MainWindow::draw(const Common::GameState &gameState)
{
	Lock startLock(m_gameStartMutex);

	if (!m_gameStarted)
		return;

	emit guiUpdateNecessary(&gameState);

	{
		Lock finishedLock(m_gameFinishedMutex);
		if (m_gameFinished)
			return;
	}

	m_guiUpdateFinished.wait();
	m_guiUpdateFinished.reset();
}

void MainWindow::startGame(
		bool enableOpenGL, const char* levelname,
		unsigned int humanPlayerCount, unsigned int computerEnemyCount,
		GameEngine::ComputerEnemyLevel computerEnemyLevel, bool mute)
{
	m_ui->pauseButton->setText(tr("pause"));
	m_gameStartMutex.lock();
	m_gameStarted = false;
	m_gameStartMutex.unlock();
	finishGame();
	m_gameFinishedMutex.lock();
	m_gameFinished = false;
	m_gameFinishedMutex.unlock();
	m_guiUpdateFinished.reset();

	string levelpath = "levels/" + string(levelname);
	m_level = new Common::LevelDefinition(Common::CSVParser(levelpath));
	if(!m_level->isLevelBuildingCorrect())
	{
		emit levelBuildingNotCorectSignal();
		return;
	}

	m_soundPlayer = new Sound::SoundPlayer(mute);
	m_gameEngine = new GameEngine::GameEngineImpl(*m_level, *m_soundPlayer, humanPlayerCount, computerEnemyCount);
	m_gameLoop = new GameLoop(*this, *m_gameEngine, *this, computerEnemyLevel);
	m_enableOpenGL = enableOpenGL;
	m_gameStartMutex.lock();
	m_gameStarted = true;
	m_gameStartMutex.unlock();

	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView), m_enableOpenGL);
	const Common::GameState &gameState = m_gameEngine->getGameState();
	vector<unsigned int> playerIDsToShow = gameState.getAllNotDestroyedHumanPlayerIDs();
	setResponsibleForPlayers(playerIDsToShow);

	connect(m_gameLoop, SIGNAL(winnerSignal()), this, SLOT(closeGame()));

	m_gameLoop->start();
	show();
	updatePauseButtonLabel();
	updateMuteButtonLabel();
	m_timerUserInfoUpdate->start(m_statusBarUpdateTimeStep);
}

void MainWindow::updateGui(const Common::GameState *gameState)
{
	{
		Lock lock(m_gameFinishedMutex);

		if (m_gameFinished)
		{
			m_guiUpdateFinished.send();
			return;
		}
	}
	m_drawer->draw(*gameState);
	m_ui->graphicsView->viewport()->update();
	m_guiUpdateFinished.send();
}

void MainWindow::updateUserInfo()
{
	{
		Lock lock(m_gameFinishedMutex);

		if (!m_gameStarted || m_gameFinished)
			return;
	}

	updateStatusBar();
	updatePlayerStateInfo();
	m_timerUserInfoUpdate->start(m_statusBarUpdateTimeStep);
}

void MainWindow::updateStatusBar()
{
	QString messageTemplate = QString("%1 fps");
	double framesPerSecond = m_gameLoop->getFramesPerSecond();
	QString framesPerSecondString = QString().setNum(framesPerSecond, 'f', 1);
	QString completeMessage(messageTemplate.arg(framesPerSecondString));

	m_ui->statusBar->showMessage(completeMessage);
}

void MainWindow::updatePlayerStateInfo()
{
	vector<unsigned int> playerInformation = m_gameLoop->getPlayerInformation();

	if(playerInformation.size() % 3 != 0)
		assert(false);

	QString messageString("");
	QString templateString("P%1 B:%2 R:%3");

	for(size_t y = 0; y < playerInformation.size() / 3; y++)
	{
		if (y!=0)
			messageString += QString("  |  ");
		messageString += QString(templateString.arg(QString().number(playerInformation.at(y*3) + 1), QString().number(playerInformation.at(y*3+1)), QString().number(playerInformation.at(y*3+2))));
	}

	m_ui->playerStateInfo->setText(messageString);
}

void MainWindow::updateMuteButtonLabel()
{
	if (m_soundPlayer->isMuted())
		m_ui->muteButton->setText("unmute");
	else
		m_ui->muteButton->setText("mute");
}

void MainWindow::updatePauseButtonLabel()
{
	if (m_gameLoop->isPaused())
		m_ui->pauseButton->setText("resume");
	else
		m_ui->pauseButton->setText("pause");
}

void MainWindow::closeEvent(QCloseEvent *)
{
	emit closeGameSignal();
}

void MainWindow::finishGame()
{
	m_gameFinishedMutex.lock();
	m_gameFinished = true;
	m_guiUpdateFinished.send();
	m_gameFinishedMutex.unlock();
	delete m_gameLoop;
	m_gameLoop = 0;
	delete m_drawer;
	m_drawer = 0;
	delete m_level;
	m_level = 0;
	delete m_gameEngine;
	m_gameEngine = 0;
	delete m_soundPlayer;
	m_soundPlayer = 0;
}

void MainWindow::closeGame()
{
	finishGame();
	this->close();
}

void MainWindow::pauseButtonPushed()
{
	if (m_gameLoop->isPaused())
		m_gameLoop->start();
	else
		m_gameLoop->pause();

	updatePauseButtonLabel();
}

void MainWindow::muteButtonPushed()
{
	if (m_soundPlayer->isMuted())
		m_soundPlayer->setMuted(false);
	else
		m_soundPlayer->setMuted(true);

	updateMuteButtonLabel();
}

