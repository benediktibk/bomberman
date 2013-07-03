#include "main/soundtestwindow.h"
#include "ui_soundtestwindow.h"
#include "sound/soundplayer.h"

using namespace Main;

SoundTestWindow::SoundTestWindow() :
	m_ui(new Ui::SoundTestWindow),
	m_sound(new Sound::SoundPlayer(false))
{
	m_ui->setupUi(this);
	connectSlots();
}

SoundTestWindow::~SoundTestWindow()
{
	delete m_sound;
}

void SoundTestWindow::connectSlots()
{
	connect(m_ui->bombButton, SIGNAL(clicked()), this, SLOT(bombExplosion()));
	connect(m_ui->placeButton, SIGNAL(clicked()), this, SLOT(bombPlaced()));
	connect(m_ui->pickUpButton, SIGNAL(clicked()), this, SLOT(gotItem()));
	connect(m_ui->wallDownButton, SIGNAL(clicked()), this, SLOT(wallDown()));
	connect(m_ui->muteCheckBox, SIGNAL(clicked()), this, SLOT(muteChanged()));
	connect(m_ui->deadButton, SIGNAL(clicked()), this, SLOT(deadPlayer()));
}

void SoundTestWindow::bombExplosion()
{
	m_sound->bombExplosion();
}

void SoundTestWindow::bombPlaced()
{
	m_sound->bombPlaced();
}

void SoundTestWindow::gotItem()
{
	m_sound->gotItem();
}

void SoundTestWindow::wallDown()
{
	m_sound->wallDown();
}

void SoundTestWindow::deadPlayer()
{
	m_sound->deadPlayer();
}

void SoundTestWindow::muteChanged()
{
	m_sound->setMuted(m_ui->muteCheckBox->isChecked());
}