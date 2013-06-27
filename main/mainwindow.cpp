#include "main/mainwindow.h"
#include "ui_mainwindow.h"
#include "graphic/graphicdrawerqt.h"
#include "common/gamestate.h"
#include "main/gameloop.h"
#include "gameengine/gameengineimpl.h"
#include <assert.h>
#include <QtCore/QTimer>
#include <QScrollBar>

using namespace Main;
using namespace Graphic;
using namespace std;

MainWindow::MainWindow() :
	m_statusBarUpdateTimeStep(250),
	m_ui(new Ui::MainWindow),
	m_drawer(0),
	m_level(0),
	m_gameEngine(0),
	m_gameLoop(0),
	m_timerUserInfoUpdate(new QTimer(this)),
	m_gameStarted(false)
{
	m_ui->setupUi(this);

	connect(	this, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	connect(	m_timerUserInfoUpdate, SIGNAL(timeout()),
				this, SLOT(updateUserInfo()));
	connect(	m_ui->pauseButton, SIGNAL(clicked()),
				this, SLOT(pauseButtonPushed()));
	m_timerUserInfoUpdate->start(m_statusBarUpdateTimeStep);
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
	m_gameStartMutex.lock();
	if (!m_gameStarted)
	{
		m_gameStartMutex.unlock();
		return;
	}

	emit guiUpdateNecessary(&gameState);
	m_guiUpdateFinished.wait();
	m_guiUpdateFinished.reset();
	m_gameStartMutex.unlock();
}

void MainWindow::startGame(bool enableOpenGL, const char* levelname, unsigned int humanPlayerCount, unsigned int computerEnemyCount, GameEngine::ComputerEnemyLevel computerEnemyLevel)
{
	m_ui->pauseButton->setText(tr("pause"));
	m_gameStartMutex.lock();
	m_gameStarted = false;
	m_gameStartMutex.unlock();
	finishGame();

	string levelpath = "levels/" + string(levelname);
	m_level = new Common::LevelDefinition(Common::CSVParser(levelpath));
	if(!m_level->isLevelBuildingCorrect())
	{
		emit levelBuildingNotCorectSignal();
		return;
	}

	m_gameEngine = new GameEngine::GameEngineImpl(*m_level, humanPlayerCount, computerEnemyCount);
	m_gameLoop = new GameLoop(*this, *m_gameEngine, *this, computerEnemyLevel);
	m_enableOpenGL = enableOpenGL;
	m_gameStartMutex.lock();
	m_gameStarted = true;
	m_gameStartMutex.unlock();

	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView), m_enableOpenGL);
	const Common::GameState &gameState = m_gameEngine->getGameState();
	vector<unsigned int> playerIDsToShow = gameState.getAllNotDestroyedHumanPlayerIDs();
	setResponsibleForPlayers(playerIDsToShow);

	m_gameLoop->start();
	show();
}

void MainWindow::updateGui(const Common::GameState *gameState)
{
	m_drawer->draw(*gameState);
	m_ui->graphicsView->viewport()->update();
	m_guiUpdateFinished.send();
}

void MainWindow::updateUserInfo()
{
	updateStatusBar();
	updatePlayerStateInfo();
	m_timerUserInfoUpdate->start(m_statusBarUpdateTimeStep);
}

void MainWindow::updateStatusBar()
{
	if(!m_gameStarted)
		return;

	QString messageTemplate = QString("%1 fps");
	double framesPerSecond = m_gameLoop->getFramesPerSecond();
	QString framesPerSecondString = QString().setNum(framesPerSecond, 'f', 1);
	QString completeMessage(messageTemplate.arg(framesPerSecondString));

	m_ui->statusBar->showMessage(completeMessage);
}

void MainWindow::updatePlayerStateInfo()
{
	if (!m_gameStarted)
		return;
	std::vector<unsigned int> playerInformation = m_gameLoop->getPlayerInformation();

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

void MainWindow::closeEvent(QCloseEvent *)
{
	emit closeGameSignal();
}

void MainWindow::finishGame()
{
	delete m_gameLoop;
	delete m_drawer;
	delete m_level;
	delete m_gameEngine;
}

void MainWindow::closeGame()
{
	this->close();
}

void MainWindow::pauseButtonPushed()
{
	if (m_gameLoop->isPaused())
	{
		m_gameLoop->start();
		m_ui->pauseButton->setText("pause");
	}
	else
	{
		m_gameLoop->pause();
		m_ui->pauseButton->setText("resume");
	}
}

