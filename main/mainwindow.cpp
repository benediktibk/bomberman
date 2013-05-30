#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtOpenGL/QGLWidget>
#include <QtCore/QTimer>
#include <QtGui/QScrollBar>
#include "graphic/graphicdrawerqt.h"
#include "common/gamestate.h"
#include "gameloop.h"
#include "gameengine/gameengineimpl.h"

using namespace Main;
using namespace Qt;
using namespace Graphic;

MainWindow::MainWindow(bool enableOpenGL) :
	m_statusBarUpdateTimeStep(250),
	m_ui(new Ui::MainWindow),
	m_drawer(0),
	m_level(Common::LevelDefinition::createDefaultLevel()),
	m_gameEngine(new GameEngine::GameEngineImpl(m_level)),
	m_gameLoop(new GameLoop(*this, *m_gameEngine)),
	m_timerStatusBarUpdate(new QTimer(this))
{
	m_ui->setupUi(this);

	if (enableOpenGL)
		m_ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

	m_ui->graphicsView->setFocusPolicy(NoFocus);
	m_ui->graphicsView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView));
	connect(	m_gameLoop, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	connect(	m_timerStatusBarUpdate, SIGNAL(timeout()),
				this, SLOT(updateStatusBar()));
	m_gameLoop->start();
	m_timerStatusBarUpdate->start(m_statusBarUpdateTimeStep);
}

MainWindow::~MainWindow()
{
	delete m_gameLoop;
	delete m_drawer;
	delete m_gameEngine;
	delete m_ui;
}

void MainWindow::updateGui(const Common::GameState *gameState)
{
	m_drawer->draw(*gameState);
	m_ui->graphicsView->setSceneRect(300, -300, 100, 100);
	m_ui->graphicsView->viewport()->update();
	m_gameLoop->setGuiUpdateFinished();
}

void MainWindow::updateStatusBar()
{
	QString message = QString("%1 fps, %2 \% of time calculating");
	double framesPerSecond = m_gameLoop->getFramesPerSecond();
	double percentageOfTimeNotSleeping = m_gameLoop->percentageOfTimeNotSleeping() * 100;
	QString framesPerSecondString = QString().setNum(framesPerSecond, 'f', 0);
	QString percentageOfTimeNotSleepingString = QString().setNum(percentageOfTimeNotSleeping, 'f', 0);
	m_ui->statusBar->showMessage(message.arg(framesPerSecondString).arg(percentageOfTimeNotSleepingString));
	m_timerStatusBarUpdate->start(m_statusBarUpdateTimeStep);
}
