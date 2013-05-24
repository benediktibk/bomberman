#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtOpenGL/QGLWidget>
#include <QtCore/QTimer>
#include "graphicdrawerqt.h"
#include "gamestate.h"
#include "gameloop.h"
#include "gameengineimpl.h"

using namespace Common;
using namespace Main;
using namespace Qt;
using namespace Graphic;

MainWindow::MainWindow() :
	m_fpsUpdateTimeStep(250),
	m_ui(new Ui::MainWindow),
	m_drawer(0),
	m_gameEngine(new GameEngine::GameEngineImpl),
	m_gameLoop(new GameLoop(*this, *m_gameEngine)),
	m_timer(new QTimer(this))
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	m_ui->graphicsView->setFocusPolicy(NoFocus);
	m_ui->graphicsView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView));
	connect(	m_gameLoop, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	connect(	m_timer, SIGNAL(timeout()),
				this, SLOT(updateFPS()));
	m_gameLoop->start();
	m_timer->start(m_fpsUpdateTimeStep);
}

MainWindow::~MainWindow()
{
	delete m_gameLoop;
	delete m_drawer;
	delete m_gameEngine;
}

void MainWindow::updateGui(const GameState *gameState)
{
	m_drawer->draw(*gameState);
	m_ui->graphicsView->viewport()->update();
	m_gameLoop->setGuiUpdateFinished();
}

void MainWindow::updateFPS()
{
	m_ui->statusBar->showMessage(QString("%1 fps").arg(m_gameLoop->getFramesPerSecond()));
	m_timer->start(m_fpsUpdateTimeStep);
}
