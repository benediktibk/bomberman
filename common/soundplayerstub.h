#ifndef COMMON_SOUNDPLAYERSTUB_H
#define COMMON_SOUNDPLAYERSTUB_H

#include "common/soundplayer.h"

namespace Common
{
    class SoundPlayerStub :
        public SoundPlayer
    {
    public:
        virtual void bombExplosion();
        virtual void bombPlaced();
        virtual void gotItem();
        virtual void wallDown();
        virtual void deadPlayer();
    };
}

#endif // SOUNDPLAYERSTUB_H
