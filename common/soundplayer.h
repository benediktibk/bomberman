#ifndef COMMON_SOUNDPLAYER_H
#define COMMON_SOUNDPLAYER_H

namespace Common
{
    class SoundPlayer
    {
    public:
        virtual void bombExplosion() = 0;

        virtual ~SoundPlayer() { }
    };
}

#endif
