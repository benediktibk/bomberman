#include "sound/soundplayer.h"
#include <QtMultimedia/QSoundEffect>

using namespace Sound;
using namespace std;

SoundPlayer::SoundPlayer() :
    m_bombExplosion(new QSoundEffect(0)),
    m_bombPlaced(new QSoundEffect(0)),
    m_gotItem(new QSoundEffect(0))
{
    m_bombExplosion->setSource(QUrl::fromLocalFile("resources/sounds/bomb.wav"));
    m_bombPlaced->setSource(QUrl::fromLocalFile("resources/sounds/placed.wav"));
    m_gotItem->setSource(QUrl::fromLocalFile("resources/sounds/gotitem.wav"));
}

SoundPlayer::~SoundPlayer()
{
    delete m_bombExplosion;
    delete m_bombPlaced;
    delete m_gotItem;
}

void SoundPlayer::bombExplosion()
{
    m_bombExplosion->play();
}

void SoundPlayer::bombPlaced()
{
    m_bombPlaced->play();
}

void SoundPlayer::gotItem()
{
    m_gotItem->play();
}
