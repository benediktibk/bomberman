#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <assert.h>

MainWindow::MainWindow() :
	QMainWindow(0),
	m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	connectButtons();
}

void MainWindow::connectButtons()
{

}