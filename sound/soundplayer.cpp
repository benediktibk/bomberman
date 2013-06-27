#include "soundplayer.h"


//QString("resources/graphics/player_moving_down_4.svg")
using namespace Sound;
using namespace std;


SoundPlayer::SoundPlayer()
{
}

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::SoundplayBombSound()
{
    QSound bombsound(QString("resources/sounds/bomb.wav"));
    bombsound.play();
}
