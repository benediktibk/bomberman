#include "startwindow.h"
#include "ui_startwindow.h"
#include <QStandardItemModel>
#include "common/csvparser.h"

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
	Common::CSVParser levellist("levels/levellist");

	QStandardItemModel *model = new QStandardItemModel(levellist.getHeightOfFile()-1,4,this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Level")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Height")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Width")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Maximum Player")));

	QStandardItem *firstRow = new QStandardItem(QString("ColumnValue"));
	model->setItem(0,0, firstRow);

	m_ui->levelTableView->setModel(model);
}

void StartWindow::exitClicked()
{
	this->close();
}

void StartWindow::startClicked()
{
}
