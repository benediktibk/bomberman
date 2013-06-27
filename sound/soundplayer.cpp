#include "sound/soundplayer.h"
#include <QtMultimedia/QSound>

using namespace Sound;
using namespace std;

SoundPlayer::SoundPlayer()
{
}

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::bombExplosion()
{
    QSound bombsound(QString("resources/sounds/bomb.wav"));
    bombsound.play();
}
