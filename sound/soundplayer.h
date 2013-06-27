#ifndef SOUND_SOUNDPLAYER_H
#define SOUND_SOUNDPLAYER_H

#include "common/soundplayer.h"
#include <vector>
#include <string>

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
        void deleteVector(std::vector<QSoundEffect*> &sounds);
        void setUpSounds(std::vector<QSoundEffect*> &sounds, const std::string &source);
        
    private:
        const unsigned int m_soundBufferSize;
        std::vector<QSoundEffect*> m_bombExplosion;
        unsigned int m_bombExplosionIndex;
        std::vector<QSoundEffect*> m_bombPlaced;
        unsigned int m_bombPlacedIndex;
        std::vector<QSoundEffect*> m_gotItem;
        unsigned int m_gotItemIndex;
    };
}

#endif
