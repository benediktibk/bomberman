#ifndef SOUND_SOUNDPLAYER_H
#define SOUND_SOUNDPLAYER_H

#include "common/soundplayer.h"

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
    };
}

#endif
