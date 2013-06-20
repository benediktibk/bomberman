#include "startwindow.h"
#include "ui_startwindow.h"

using namespace std;
using namespace Main;

StartWindow::StartWindow() :
	m_ui(new Ui::StartWindow)
{
	m_ui->setupUi(this);
	connectButtons();
}

void StartWindow::connectButtons()
{
	connect(m_ui->exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));
	connect(m_ui->startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
}

void StartWindow::exitClicked()
{
	this->close();
}

void StartWindow::startClicked()
{
}
