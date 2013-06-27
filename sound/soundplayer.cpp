#include "sound/soundplayer.h"
#include <QtMultimedia/QSound>

using namespace Sound;
using namespace std;

SoundPlayer::SoundPlayer() :
    m_bombExplosion(new QSound(QString("resources/sounds/bomb.wav")))
{ }

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::bombExplosion()
{
    m_bombExplosion->play();
}
