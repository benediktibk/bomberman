#include "startwindow.h"
#include "ui_startwindow.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <assert.h>

using namespace std;
using namespace Main;
using namespace GameEngine;

StartWindow::StartWindow(bool enableOpenGL) :
	m_ui(new Ui::StartWindow),
	m_levelList(Common::CSVParser("levels/levellist"))
{
	m_ui->setupUi(this);
	connectButtons();
	createTableView();
	createSilder();
	createComboBox();
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
	connect(m_ui->singleRadioButton, SIGNAL(clicked()), this, SLOT(updateSilder()));
	connect(m_ui->multiRadioButton, SIGNAL(clicked()), this, SLOT(updateSilder()));
	connect(m_ui->controlButton, SIGNAL(clicked()), this, SLOT(controlClicked()));
	connect(m_ui->readMeButton, SIGNAL(clicked()), this, SLOT(readMeClicked()));
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
	m_ui->levelTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	m_ui->levelTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_ui->levelTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_ui->levelTableView->setModel(model);
	m_ui->levelTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	m_ui->levelTableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

	connect(m_ui->levelTableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(updateSilder()));
}

void StartWindow::createSilder()
{
	connect( m_ui->playerCountHorizontalSlider, SIGNAL( valueChanged(int)), this, SLOT(showHorizontalSliderValue()));
	m_ui->playerCountHorizontalSlider->setMaximum(m_ui->levelTableView->model()->data(m_ui->levelTableView->model()->index(0,3)).toInt()-1);
}

void StartWindow::createComboBox()
{
	m_ui->difficultyComboBox->addItem("easy");
	m_ui->difficultyComboBox->addItem("medium");
	m_ui->difficultyComboBox->addItem("hard");
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
		ComputerEnemyLevel computerEnemyLevel = ComputerEnemyLevelEasy;

		QString selectedComputerEnemyLevel = m_ui->difficultyComboBox->currentText();
		if (selectedComputerEnemyLevel == "easy")
			computerEnemyLevel = ComputerEnemyLevelEasy;
		else if (selectedComputerEnemyLevel == "medium")
			computerEnemyLevel = ComputerEnemyLevelMedium;
		else if (selectedComputerEnemyLevel == "hard")
			computerEnemyLevel = ComputerEnemyLevelHard;
		else
			assert(false);

		unsigned int humanPlayerCount = 0;

		if (m_ui->singleRadioButton->isChecked())
			humanPlayerCount = 1;
		else if (m_ui->multiRadioButton->isChecked())
			humanPlayerCount = 2;
		else
			assert(false);

		emit startGameSignal(
					m_ui->openGlCheckBox->isChecked(), m_selectedLevel.c_str(),
					humanPlayerCount, m_ui->playerCountHorizontalSlider->value(),
					computerEnemyLevel, m_ui->muteCheckBox->isChecked());
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
	if(m_ui->singleRadioButton->isChecked())
	{
		m_ui->playerCountHorizontalSlider->setMinimum(1);
		m_ui->playerCountHorizontalSlider->setMaximum(m_ui->levelTableView->model()->data(m_ui->levelTableView->selectionModel()->selectedIndexes().at(3)).toInt()-1);
	}
	else
	{
		m_ui->playerCountHorizontalSlider->setMinimum(0);
		m_ui->playerCountHorizontalSlider->setMaximum(m_ui->levelTableView->model()->data(m_ui->levelTableView->selectionModel()->selectedIndexes().at(3)).toInt()-2);
	}

}

void StartWindow::readMeClicked()
{
	QMessageBox messageBox;
	messageBox.setWindowTitle("README");
	QSpacerItem* horizontalSpacer = new QSpacerItem(600, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	QGridLayout* layout = (QGridLayout*)messageBox.layout();
	layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
	messageBox.setText(Common::CSVParser("README/README").getTextInFile().c_str());
	messageBox.setDetailedText(Common::CSVParser("README/README_Details").getTextInFile().c_str());
	messageBox.exec();
}

void StartWindow::controlClicked()
{
	QMessageBox messageBox;
	messageBox.setWindowTitle("Control");
	messageBox.setText("Player 1:\trun:\tarrow keys \n\tbomb:\tspace\nPlayer 2:\trun:\tW A S D \n\tbomb:\tQ");
	messageBox.exec();
}

void StartWindow::winnerOfGame(const char *winner)
{
	QMessageBox messageBox;
	messageBox.setIcon(QMessageBox::Information);
	messageBox.setWindowTitle("GAME OVER");
	messageBox.setText(winner);
	messageBox.exec();
}
