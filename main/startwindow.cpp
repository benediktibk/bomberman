#include "startwindow.h"
#include "ui_startwindow.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include "common/csvparser.h"

using namespace std;
using namespace Main;

StartWindow::StartWindow(bool enableOpenGL) :
	m_ui(new Ui::StartWindow)
{
	m_ui->setupUi(this);
	connectButtons();
	connectTableView();
	if(enableOpenGL)
		m_ui->openGlCheckBox->setChecked(true);
}

void StartWindow::connectButtons()
{
	connect(m_ui->exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));
	connect(m_ui->startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
	connect(m_ui->closeGameButton, SIGNAL(clicked()), this, SLOT(closeGameClicked()));
}

void StartWindow::connectTableView()
{
	Common::CSVParser levellist("levels/levellist");

	QStandardItemModel *model = new QStandardItemModel(levellist.getHeightOfFile()-1,4,this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Level")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Height")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Width")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Maximum Player")));

	for (unsigned int row = 0; row < levellist.getHeightOfFile()-1; ++row)
		for (unsigned int column = 0; column < 4; ++column)
		{
			QStandardItem *currentItem = new QStandardItem(QString(levellist.getTextInField(column, row).c_str()));
			model->setItem(row, column, currentItem);
		}

	m_ui->levelTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_ui->levelTableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_ui->levelTableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	m_ui->levelTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_ui->levelTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_ui->levelTableView->setModel(model);
}

void StartWindow::exitClicked()
{
	emit closeGameSignal();
	this->close();
}

void StartWindow::startClicked()
{
	m_selectedLevel = "defaultlevel";
	if(m_selectedLevel == "")
		m_ui->infoLabel->setText(tr("please select a level from the upper table !!!"));
	else
	{
		emit startGameSignal(m_ui->openGlCheckBox->isChecked(), m_selectedLevel.c_str());
	}
}

void StartWindow::closeGameClicked()
{
	emit closeGameSignal();
}

void StartWindow::levelBuildingNotCorrect()
{
	m_ui->infoLabel->setText(tr("levelbuilding was not correct!!! \nerror in file or filename!!!"));
}
