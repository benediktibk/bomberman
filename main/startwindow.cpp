#include "startwindow.h"
#include "ui_startwindow.h"
#include <QStandardItemModel>

using namespace std;
using namespace Main;

StartWindow::StartWindow() :
	m_ui(new Ui::StartWindow)
{
	m_ui->setupUi(this);
	connectButtons();
	connectTableView();
}

void StartWindow::connectButtons()
{
	connect(m_ui->exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));
	connect(m_ui->startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
}

void StartWindow::connectTableView()
{
	QStandardItemModel *model = new QStandardItemModel(2,3,this); //2 Rows and 3 Columns
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Column1 Header")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Column2 Header")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Column3 Header")));

	m_ui->levelTableView->setModel(model);
}

void StartWindow::exitClicked()
{
	this->close();
}

void StartWindow::startClicked()
{
}
