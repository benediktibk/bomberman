#ifndef COMMON_SOUNDPLAYER_H
#define COMMON_SOUNDPLAYER_H

namespace Common
{
    class SoundPlayer
    {
    public:
        virtual void bombExplosion() = 0;
        virtual void bombPlaced() = 0;
        virtual void gotItem() = 0;
        virtual void wallDown() = 0;
        virtual void deadPlayer() = 0;
        virtual ~SoundPlayer() { }
    };
}

#endif
