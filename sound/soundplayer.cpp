#include "sound/soundplayer.h"
#include <QtMultimedia/QSoundEffect>

using namespace Sound;
using namespace std;

SoundPlayer::SoundPlayer() :
    m_bombExplosion(new QSoundEffect(0))
{
    m_bombExplosion->setSource(QUrl::fromLocalFile("resources/sounds/bomb.wav"));
}

SoundPlayer::~SoundPlayer()
{
    delete m_bombExplosion;
}

void SoundPlayer::bombExplosion()
{
    m_bombExplosion->play();
}
