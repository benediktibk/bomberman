#include "main/mainwindow.h"
#include "ui_mainwindow.h"
#include "graphic/graphicdrawerqt.h"
#include "common/gamestate.h"
#include "main/gameloop.h"
#include "gameengine/gameengineimpl.h"
#include <QtCore/QTimer>
#include <QtGui/QScrollBar>

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
	m_timerStatusBarUpdate(new QTimer(this)),
	m_gameStarted(false)
{
	m_ui->setupUi(this);

	connect(	this, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	connect(	m_timerStatusBarUpdate, SIGNAL(timeout()),
				this, SLOT(updateStatusBar()));
	m_timerStatusBarUpdate->start(m_statusBarUpdateTimeStep);
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

void MainWindow::startGame(bool enableOpenGL, const char* levelname)
{
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
	m_gameEngine = new GameEngine::GameEngineImpl(*m_level, 2);
	m_gameLoop = new GameLoop(*this, *m_gameEngine, *this);
	m_enableOpenGL = enableOpenGL;
	m_gameStartMutex.lock();
	m_gameStarted = true;
	m_gameStartMutex.unlock();

	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView), m_enableOpenGL);
	vector<unsigned int> playerIDs = m_gameEngine->getAllPossiblePlayerIDs();
	vector<unsigned int> playerIDsToShow;
	playerIDsToShow.push_back(playerIDs.front());
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

void MainWindow::updateStatusBar()
{
	QString messageTemplate = QString("%1 fps");

	if (!m_enableOpenGL)
		messageTemplate += QString(", %2\% of time calculating");

	if(!m_gameStarted)
		return;

	double framesPerSecond = m_gameLoop->getFramesPerSecond();
	double percentageOfTimeNotSleeping = m_gameLoop->percentageOfTimeNotSleeping() * 100;
	QString framesPerSecondString = QString().setNum(framesPerSecond, 'f', 0);
	QString percentageOfTimeNotSleepingString = QString().setNum(percentageOfTimeNotSleeping, 'f', 0);
	QString completeMessage(messageTemplate.arg(framesPerSecondString));

	if (!m_enableOpenGL)
		completeMessage = completeMessage.arg(percentageOfTimeNotSleepingString);

	m_ui->statusBar->showMessage(completeMessage);
	m_timerStatusBarUpdate->start(m_statusBarUpdateTimeStep);
}


void MainWindow::finishGame()
{
	delete m_gameLoop;
	delete m_drawer;
	delete m_level;
	delete m_gameEngine;
}
