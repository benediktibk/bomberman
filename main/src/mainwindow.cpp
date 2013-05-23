#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtOpenGL/QGLWidget>
#include "graphicdrawerqt.h"
#include "gamestate.h"
#include "gameloop.h"

using namespace Common;
using namespace Main;
using namespace Qt;
using namespace Graphic;

MainWindow::MainWindow() :
	m_ui(new Ui::MainWindow),
	m_drawer(0),
	m_signalGuiUpdateFinished(0)
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	m_ui->graphicsView->setFocusPolicy(NoFocus);
	m_drawer = new GraphicDrawerQt(*(m_ui->graphicsView));
}

MainWindow::~MainWindow()
{
	delete m_drawer;
}

QGraphicsView& MainWindow::getGraphicsView()
{
	return *(m_ui->graphicsView);
}

void MainWindow::setSignalGuiUpdateFinished(Threading::Signal &signal)
{
	m_signalGuiUpdateFinished = &signal;
}

void MainWindow::updateGui(const GameState *gameState)
{
	m_drawer->draw(*gameState);

	if (m_signalGuiUpdateFinished != 0)
		m_signalGuiUpdateFinished->send();
}
