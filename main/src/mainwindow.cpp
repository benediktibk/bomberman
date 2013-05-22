#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtOpenGL/QGLWidget>

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindow::MainWindow() :
	m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	m_ui->graphicsView->setFocusPolicy(NoFocus);
}

QGraphicsView& MainWindow::getGraphicsView()
{
	return *(m_ui->graphicsView);
}
