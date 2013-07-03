#include "main/gamewindow.h"
#include "main/gameloop.h"
#include "ui_gamewindow.h"
#include "graphic/graphicdrawerqt.h"
#include "common/gamestate.h"
#include "gameengine/gameengineimpl.h"
#include "gameengine/allplayerinputfetcher.h"
#include "sound/soundplayer.h"
#include "threading/lock.h"
#include <assert.h>
#include <QtCore/QTimer>
#include <QScrollBar>

using namespace Main;
using namespace Graphic;
using namespace Threading;
using namespace std;

GameWindow::GameWindow() :
	m_statusBarUpdateTimeStep(250),
	m_ui(new Ui::GameWindow),
	m_drawer(0),
	m_level(0),
	m_gameEngine(0),
	m_soundPlayer(0),
	m_gameLoop(0),
	m_allPlayerInputFetcher(0),
	m_timerUserInfoUpdate(new QTimer(this)),
	m_gameRunning(false)
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
	connect(    m_ui->volumeHorizontalSlider, SIGNAL(sliderReleased()),
				this, SLOT(volumeChanged()));
	m_drawFinished.send();
}

GameWindow::~GameWindow()
{
	m_guiUpdateFinished.send();
	finishGame();
	freeMemory();
	delete m_ui;
}

void GameWindow::setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs)
{
	m_drawer->setResponsibleForPlayers(playerIDs);
}

void GameWindow::draw(const Common::GameState &gameState)
{
	m_drawFinished.reset();

	{
		Lock lock(m_gameRunningMutex);

		if (!m_gameRunning)
		{
			m_drawFinished.send();
			return;
		}
	}

	emit guiUpdateNecessary(&gameState);

	m_guiUpdateFinished.wait();

	{
		Lock lock(m_gameRunningMutex);

		if (m_gameRunning)
			m_guiUpdateFinished.reset();
	}

	m_drawFinished.send();
}

void GameWindow::startGame(
		bool enableOpenGL, const char* levelName,
		unsigned int humanPlayerCount, unsigned int computerEnemyCount,
		GameEngine::ComputerEnemyLevel computerEnemyLevel, bool mute)
{
	finishGame();
	freeMemory();

	if (!createLevel(levelName))
		return;

	createSoundPlayer(mute);
	createGameEngine(humanPlayerCount, computerEnemyCount);
	createAllPlayerInputFetcher(computerEnemyLevel);
	createGameLoop();
	createDrawer(enableOpenGL);

	m_gameRunning = true;
	m_drawFinished.send();
	m_gameLoop->start();

	show();
	updatePauseButtonLabel();
	updateMuteButtonLabel();
	m_timerUserInfoUpdate->start(m_statusBarUpdateTimeStep);
}

void GameWindow::updateGui(const Common::GameState *gameState)
{
	m_drawer->draw(*gameState);
	m_ui->graphicsView->viewport()->update();
	m_guiUpdateFinished.send();
}

void GameWindow::updateUserInfo()
{
	if (!m_gameRunning)
		return;

	updateStatusBar();
	updatePlayerStateInfo();
	m_timerUserInfoUpdate->start(m_statusBarUpdateTimeStep);
}

void GameWindow::updateStatusBar()
{
	QString messageTemplate = QString("%1 fps");
	double framesPerSecond = m_gameLoop->getFramesPerSecond();
	QString framesPerSecondString = QString().setNum(framesPerSecond, 'f', 1);
	QString completeMessage(messageTemplate.arg(framesPerSecondString));

	m_ui->statusBar->showMessage(completeMessage);
}

void GameWindow::updatePlayerStateInfo()
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

void GameWindow::updateMuteButtonLabel()
{
	if (m_soundPlayer->isMuted())
		m_ui->muteButton->setText("unmute");
	else
		m_ui->muteButton->setText("mute");
}

void GameWindow::updatePauseButtonLabel()
{
	if (m_gameLoop->isPaused())
		m_ui->pauseButton->setText("resume");
	else
		m_ui->pauseButton->setText("pause");
}

void GameWindow::closeEvent(QCloseEvent *)
{
	emit closeGameSignal();
}

void GameWindow::finishGame()
{
	if (m_gameLoop != 0)
	{
		m_gameRunningMutex.lock();
		m_gameRunning = false;
		m_guiUpdateFinished.send();
		m_gameRunningMutex.unlock();
		m_gameLoop->stop();
		m_gameLoop->waitTillFinished();
	}

	m_drawFinished.wait();
	m_guiUpdateFinished.reset();

	freeMemory();
}

void GameWindow::closeGame()
{
	finishGame();
	this->close();
}

void GameWindow::winnerOfGame(int winner)
{
	emit winnerOfGameSignal(winner);
	closeGame();
}

void GameWindow::pauseButtonPushed()
{
	if (m_gameLoop->isPaused())
		m_gameLoop->start();
	else
		m_gameLoop->pause();

	updatePauseButtonLabel();
}

void GameWindow::muteButtonPushed()
{
	if (m_soundPlayer->isMuted())
		m_soundPlayer->setMuted(false);
	else
		m_soundPlayer->setMuted(true);

	updateMuteButtonLabel();
}

void GameWindow::volumeChanged()
{
	double range = m_ui->volumeHorizontalSlider->maximum() - m_ui->volumeHorizontalSlider->minimum();
	double volume = m_ui->volumeHorizontalSlider->value()/range;
	m_soundPlayer->setVolume(volume);
}

bool GameWindow::createLevel(const string &levelName)
{
	assert(m_level == 0);
	string levelNameWithPath = "levels/" + string(levelName);
	m_level = new Common::LevelDefinition(Common::CSVParser(levelNameWithPath));

	if(!m_level->isLevelBuildingCorrect())
	{
		emit levelBuildingNotCorectSignal();
		return false;
	}
	else
		return true;
}

void GameWindow::createGameLoop()
{
	assert(m_gameLoop == 0);
	m_gameLoop = new GameLoop(*m_allPlayerInputFetcher, *m_gameEngine, *this);
	connect(m_gameLoop, SIGNAL(winnerSignal(int)), this, SLOT(winnerOfGame(int)));
}

void GameWindow::createDrawer(bool enableOpenGL)
{
	assert(m_drawer == 0);
	const Common::GameState &gameState = m_gameEngine->getGameState();
	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView), enableOpenGL);
	vector<unsigned int> playerIDsToShow = gameState.getAllNotDestroyedHumanPlayerIDs();
	setResponsibleForPlayers(playerIDsToShow);
}

void GameWindow::createSoundPlayer(bool mute)
{
	assert(m_soundPlayer == 0);
	m_soundPlayer = new Sound::SoundPlayer(mute);
	m_ui->volumeHorizontalSlider->setValue(static_cast<int>(m_soundPlayer->getVolume()*(m_ui->volumeHorizontalSlider->maximum() - m_ui->volumeHorizontalSlider->minimum())));
}

void GameWindow::createGameEngine(unsigned int humanPlayerCount, unsigned int computerEnemyCount)
{
	assert(m_gameEngine == 0);
	m_gameEngine = new GameEngine::GameEngineImpl(*m_level, *m_soundPlayer, humanPlayerCount, computerEnemyCount);
}

void GameWindow::createAllPlayerInputFetcher(GameEngine::ComputerEnemyLevel computerEnemyLevel)
{
	assert(m_allPlayerInputFetcher == 0);
	const Common::GameState &gameState = m_gameEngine->getGameState();
	m_allPlayerInputFetcher = new GameEngine::AllPlayerInputFetcher(*this, gameState, computerEnemyLevel, m_gameEngine->getGrid());
}

void GameWindow::freeMemory()
{
	delete m_gameLoop;
	m_gameLoop = 0;
	delete m_drawer;
	m_drawer = 0;
	delete m_level;
	m_level = 0;
	delete m_allPlayerInputFetcher;
	m_allPlayerInputFetcher = 0;
	delete m_gameEngine;
	m_gameEngine = 0;
	delete m_soundPlayer;
	m_soundPlayer = 0;
}
