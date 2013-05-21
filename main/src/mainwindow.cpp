#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <assert.h>
#include <QKeyEvent>

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindow::MainWindow(QGraphicsScene &scene) :
	QMainWindow(0),
	m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setScene(&scene);
}

InputState MainWindow::getInputState()
{
	m_inputStateMutex.lock();
	InputState stateCopy = m_inputState;
	m_inputStateMutex.unlock();
	return stateCopy;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	m_inputStateMutex.lock();
	switch (event->key())
	{
	case Key_Up:
		m_inputState.setUpKeyPressed();
		break;
	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
	m_inputStateMutex.unlock();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
	m_inputStateMutex.lock();
	switch (event->key())
	{
	case Key_Up:
		m_inputState.setUpKeyNotPressed();
		break;
	default:
		QMainWindow::keyPressEvent(event);
		break;
	}
	m_inputStateMutex.unlock();
}