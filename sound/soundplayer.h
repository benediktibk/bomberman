#ifndef SOUND_SOUNDPLAYER_H
#define SOUND_SOUNDPLAYER_H

#include "common/soundplayer.h"

class QSoundEffect;

namespace Sound
{
    class SoundPlayer :
        public Common::SoundPlayer
    {
    public:
        SoundPlayer();
        virtual ~SoundPlayer();

        virtual void bombExplosion();

    private:
        QSoundEffect *m_bombExplosion;
    };
}

#endif
