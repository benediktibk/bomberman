#ifndef SOUND_SOUNDPLAYER_H
#define SOUND_SOUNDPLAYER_H

#include "common/soundplayer.h"
#include <vector>

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
        virtual void bombPlaced();
        virtual void gotItem();
    private:
        std::vector<QSoundEffect*> m_bombExplosion;
        std::vector<QSoundEffect*> m_bombPlaced;
        std::vector<QSoundEffect*> m_gotItem;
    };
}

#endif
