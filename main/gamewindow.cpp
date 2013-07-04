#include "main/gamewindow.h"
#include "main/gameloop.h"
#include "ui_gamewindow.h"
#include "graphic/graphicdrawerqt.h"
#include "common/gamestate.h"
#include "common/playerinformation.h"
#include "common/stopwatch.h"
#include "gameengine/gameengineimpl.h"
#include "gameengine/allplayerinputfetcher.h"
#include "sound/soundplayer.h"
#include "threading/lock.h"
#include <assert.h>
#include <QtCore/QTimer>
#include <QtWidgets/QScrollBar>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QGraphicsView>

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
	m_timerStatusInformationUpdate(new QTimer(this)),
	m_timerUpdateViewPorts(new QTimer(this)),
	m_gameRunning(false),
	m_viewOne(0),
	m_viewTwo(0),
	m_framesPerSecondWatch(new Common::StopWatch()),
	m_timeForViewPortUpdates(0)
{
	m_ui->setupUi(this);

	connect(	this, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	connect(	m_timerStatusInformationUpdate, SIGNAL(timeout()),
				this, SLOT(updateStatusInformation()));
	connect(	m_ui->pauseButton, SIGNAL(clicked()),
				this, SLOT(pauseButtonPushed()));
	connect(	m_ui->muteButton, SIGNAL(clicked()),
				this, SLOT(muteButtonPushed()));
	connect(	this, SIGNAL(pauseButtonPressed()),
				this, SLOT(pauseButtonPushed()));
	connect(	this, SIGNAL(muteButtonPressed()),
				this, SLOT(muteButtonPushed()));
	connect(    m_ui->volumeHorizontalSlider, SIGNAL(valueChanged(int)),
				this, SLOT(volumeChanged()));
	connect(	m_timerUpdateViewPorts, SIGNAL(timeout()),
				this, SLOT(updateViewPorts()));
	m_drawFinished.send();
}

GameWindow::~GameWindow()
{
	m_guiUpdateFinished.send();
	finishGame();
	freeMemory();
	delete m_ui;
	m_ui = 0;
	delete m_framesPerSecondWatch;
	m_framesPerSecondWatch = 0;
}

void GameWindow::setResponsibleForPlayers(const vector<unsigned int> &playerIDs)
{
	assert(playerIDs.size() == 1 || playerIDs.size() == 2);
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
	createViews(humanPlayerCount);
	createDrawer(enableOpenGL);

	m_gameRunning = true;
	m_drawFinished.send();
	m_gameLoop->start();

	showMaximized();
	updatePauseButtonLabel();
	updateMuteButtonLabel();
	m_timerStatusInformationUpdate->start(m_statusBarUpdateTimeStep);
	m_timeForViewPortUpdates = 0;
	m_timerUpdateViewPorts->start(0);
}

void GameWindow::updateGui(const Common::GameState *gameState)
{
	if (m_drawer != 0)
		m_drawer->draw(*gameState);
	m_guiUpdateFinished.send();
}

void GameWindow::updateViewPorts()
{
	if (!m_gameRunning)
		return;

	for (vector<QGraphicsView*>::iterator i = m_viewsAsVector.begin(); i != m_viewsAsVector.end(); ++i)
		(*i)->viewport()->update();
	m_timerUpdateViewPorts->start(0);
	double timeSinceLastViewPortUpdate = m_framesPerSecondWatch->getTimeAndRestart();
	m_timeForViewPortUpdates = m_timeForViewPortUpdates*39.0/40 + timeSinceLastViewPortUpdate*1.0/40;
}

void GameWindow::updateStatusInformation()
{
	if (!m_gameRunning)
		return;

	updateStatusBar();
	updatePlayerStateInfo();
	m_timerStatusInformationUpdate->start(m_statusBarUpdateTimeStep);
}

void GameWindow::updateStatusBar()
{
	QString messageTemplate = QString("%1 frames per second, %2 game updates per second");
	double framesPerSecond = 1.0/m_timeForViewPortUpdates;
	QString framesPerSecondString = QString().setNum(framesPerSecond, 'f', 1);
	double gameUpdatesPerSecond = m_gameLoop->getGameUpdatesPerSecond();
	QString gameUpdatesPerSecondString = QString().setNum(gameUpdatesPerSecond, 'f', 1);
	QString completeMessage(messageTemplate.arg(framesPerSecondString).arg(gameUpdatesPerSecondString));

	m_ui->statusBar->showMessage(completeMessage);
}

void GameWindow::updatePlayerStateInfo()
{
	vector<Common::PlayerInformation> playerInformation = m_gameLoop->getPlayerInformation();
	QString messageString("");
	QString templateString("P%1 B:%2 R:%3 S%4");

	for(size_t y = 0; y < playerInformation.size(); y++)
	{
		if (y!=0)
			messageString += QString("  |  ");
		messageString += QString(templateString.arg(QString().number(playerInformation[y].getPlayerId()), QString().number(playerInformation[y].getBombCounter()), QString().number(playerInformation[y].getRangeCounter()), QString().number(playerInformation[y].getSpeedCounter())));
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

	m_drawer = new GraphicDrawerQt(m_viewsAsVector, enableOpenGL);
	const Common::GameState &gameState = m_gameEngine->getGameState();
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

void GameWindow::createViews(unsigned int humanPlayerCount)
{
	assert(m_viewOne == 0);
	assert(m_viewTwo == 0);
	assert(m_viewsAsVector.size() == 0);
	assert(humanPlayerCount == 1 || humanPlayerCount == 2);

	m_viewOne = createView();
	m_ui->viewLayout->addWidget(m_viewOne);

	if (humanPlayerCount == 2)
	{
		m_viewTwo = createView();
		m_ui->viewLayout->addWidget(m_viewTwo);
	}

	/*!
	 * The order of push-backs is important here, as it determines the left and right view and
	 * which player is shown on which view.
	 */
	if (humanPlayerCount == 2)
		m_viewsAsVector.push_back(m_viewTwo);
	m_viewsAsVector.push_back(m_viewOne);
}

QGraphicsView* GameWindow::createView()
{
	QGraphicsView *view = new QGraphicsView();
	view->setFocusPolicy(Qt::NoFocus);
	view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	view->installEventFilter(this);
	return view;
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
	delete m_viewOne;
	m_viewOne = 0;
	delete m_viewTwo;
	m_viewTwo = 0;
	m_viewsAsVector.clear();
}

bool GameWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
		keyPressEvent(keyEvent);
		return true;
	}
	else if (event->type() == QEvent::KeyRelease)
	{
		QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
		keyReleaseEvent(keyEvent);
		return true;
	}
	else
		return QObject::eventFilter(obj, event);
}
