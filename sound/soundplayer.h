#ifndef SOUND_SOUNDPLAYER_H
#define SOUND_SOUNDPLAYER_H
#include<QtMultimedia/QSound>
namespace Sound
{
    class SoundPlayer
    {
    public:
        SoundPlayer();
        ~SoundPlayer();
        void SoundplayBombSound();
    };
}

#endif
