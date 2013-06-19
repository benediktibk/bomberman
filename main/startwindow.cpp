#include "startwindow.h"
#include "ui_startwindow.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"

using namespace Common;
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
}

void StartWindow::exitClicked()
{
	this->close();
}
