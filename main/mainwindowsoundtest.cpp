#include "mainwindowsoundtest.h"
#include "ui_mainwindowsoundtest.h"
#include "sound/soundplayer.h"
using namespace Main;

MainWindowSoundTest::MainWindowSoundTest() :
	m_ui(new Ui::MainWindowSoundTest),
	m_sound(new Sound::SoundPlayer(false))
{
	m_ui->setupUi(this);
	connectSlots();
}

MainWindowSoundTest::~MainWindowSoundTest()
{
	delete m_sound;
}

void MainWindowSoundTest::connectSlots()
{
	connect(m_ui->bombButton, SIGNAL(clicked()), this, SLOT(bombExplosion()));
	connect(m_ui->placeButton, SIGNAL(clicked()), this, SLOT(bombPlaced()));
	connect(m_ui->pickUpButton, SIGNAL(clicked()), this, SLOT(gotItem()));
	connect(m_ui->wallDownButton, SIGNAL(clicked()), this, SLOT(wallDown()));
	connect(m_ui->muteCheckBox, SIGNAL(clicked()), this, SLOT(muteChanged()));
}

void MainWindowSoundTest::bombExplosion()
{
	m_sound->bombExplosion();
}

void MainWindowSoundTest::bombPlaced()
{
	m_sound->bombPlaced();
}

void MainWindowSoundTest::gotItem()
{
	m_sound->gotItem();
}

void MainWindowSoundTest::wallDown()
{
	m_sound->wallDown();
}

void MainWindowSoundTest::muteChanged()
{
	m_sound->setMuted(m_ui->muteCheckBox->isChecked());
}