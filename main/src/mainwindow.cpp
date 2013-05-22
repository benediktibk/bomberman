#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindow::MainWindow(QGraphicsScene &scene) :
	m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setScene(&scene);
}
