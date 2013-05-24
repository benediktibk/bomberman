#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtOpenGL/QGLWidget>
#include "graphicdrawerqt.h"
#include "gamestate.h"
#include "gameloop.h"
#include "gameengineimpl.h"

using namespace Common;
using namespace Main;
using namespace Qt;
using namespace Graphic;

MainWindow::MainWindow() :
	m_ui(new Ui::MainWindow),
	m_drawer(0),
	m_gameEngine(new GameEngine::GameEngineImpl),
	m_gameLoop(new GameLoop(*this, *m_gameEngine))

{
	m_ui->setupUi(this);
	m_ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	m_ui->graphicsView->setFocusPolicy(NoFocus);
	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView));
	connect(	m_gameLoop, SIGNAL(guiUpdateNecessary(const Common::GameState*)),
				this, SLOT(updateGui(const Common::GameState*)));
	m_gameLoop->start();
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
	m_gameLoop->setGuiUpdateFinished();
}
