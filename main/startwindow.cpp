#include "startwindow.h"
#include "ui_startwindow.h"
#include "mainwindow.h"
#include <QStandardItemModel>

using namespace std;
using namespace Main;

StartWindow::StartWindow(bool enableOpenGL) :
	m_ui(new Ui::StartWindow),
	m_levelList(Common::CSVParser("levels/levellist"))
{
	m_ui->setupUi(this);
	connectButtons();
	createTableView();
	createSilder();
	if(enableOpenGL)
		m_ui->openGlCheckBox->setChecked(true);
	m_ui->singleRadioButton->setChecked(true);
	m_ui->levelTableView->selectRow(0);
}

void StartWindow::connectButtons()
{
	connect(m_ui->exitButton, SIGNAL(clicked()), this, SLOT(exitClicked()));
	connect(m_ui->startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
	connect(m_ui->closeGameButton, SIGNAL(clicked()), this, SLOT(closeGameClicked()));
}

void StartWindow::createTableView()
{
	QStandardItemModel *model = new QStandardItemModel(m_levelList.getHeightOfFile()-1,4,this);
	model->setHorizontalHeaderItem(0, new QStandardItem(QString("Level")));
	model->setHorizontalHeaderItem(1, new QStandardItem(QString("Height")));
	model->setHorizontalHeaderItem(2, new QStandardItem(QString("Width")));
	model->setHorizontalHeaderItem(3, new QStandardItem(QString("Maximum Player")));

	for (unsigned int row = 0; row < m_levelList.getHeightOfFile()-1; ++row)
		for (unsigned int column = 0; column < 4; ++column)
		{
			QStandardItem *currentItem = new QStandardItem(QString(m_levelList.getTextInField(column, row).c_str()));
			model->setItem(row, column, currentItem);
		}

	m_ui->levelTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_ui->levelTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->levelTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	m_ui->levelTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_ui->levelTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_ui->levelTableView->setModel(model);
}

void StartWindow::createSilder()
{
	connect( m_ui->playerCountHorizontalSlider, SIGNAL( valueChanged(int)), this, SLOT(showHorizontalSliderValue()));
	m_ui->playerCountHorizontalSlider->setMaximum(m_ui->levelTableView->model()->data(m_ui->levelTableView->model()->index(0,3)).toInt());
}

void StartWindow::exitClicked()
{
	emit closeGameSignal();
	this->close();
}

void StartWindow::startClicked()
{
	if(m_ui->levelTableView->selectionModel()->hasSelection())
		m_selectedLevel = m_levelList.getTextInField(4, m_ui->levelTableView->selectionModel()->selectedIndexes().first().row());

	if(m_selectedLevel == "")
		m_ui->infoLabel->setText(tr("Please select a level from the upper table !!!"));
	else
	{
		string showString = "You are playing " + m_levelList.getTextInField(0, m_ui->levelTableView->selectionModel()->selectedIndexes().first().row());
		m_ui->infoLabel->setText(QString(showString.c_str()));
		emit startGameSignal(m_ui->openGlCheckBox->isChecked(), m_selectedLevel.c_str());
	}
}

void StartWindow::closeGameClicked()
{
	emit closeGameSignal();
	m_ui->infoLabel->setText(tr("GAME OVER\nPlease select a level and press Start to play"));
}

void StartWindow::levelBuildingNotCorrect()
{
	m_ui->infoLabel->setText(tr("Levelbuilding was not correct!!! \nError in file or filename!!!"));
}

void StartWindow::showHorizontalSliderValue()
{
	m_ui->sliderShowLabel->setText(QString::number(m_ui->playerCountHorizontalSlider->value()));
}

void StartWindow::updateSilder()
{

}
