#ifndef SOUND_SOUNDPLAYER_H
#define SOUND_SOUNDPLAYER_H

#include "common/soundplayer.h"
#include <vector>
#include <string>

class QSoundEffect;

namespace Threading
{
	class Mutex;
}

namespace Sound
{
	class SoundPlayer :
		public Common::SoundPlayer
	{
	public:
		SoundPlayer(bool mute);
		virtual ~SoundPlayer();

		virtual void bombExplosion();
		virtual void bombPlaced();
		virtual void gotItem();
		virtual void wallDown();
        virtual void deadPlayer();
		void setMuted(bool value);
		bool isMuted() const;
        void setVolume(double value);
        double getVolume() const;

	private:
		void deleteVector(std::vector<QSoundEffect*> &sounds);
		void setUpSounds(std::vector<QSoundEffect*> &sounds, const std::string &source, unsigned int bufferSize);
		void muteSounds(std::vector<QSoundEffect*> &sounds, bool value);
        void changeVolume(std::vector<QSoundEffect*> &sounds, double value);

	private:
		const unsigned int m_soundBombBufferSize;
		const unsigned int m_soundPlacedBufferSize;
        const unsigned int m_soundItemBufferSize;
        const unsigned int m_soundWallBufferSize;
        const unsigned int m_soundDeadBufferSize;
		std::vector<QSoundEffect*> m_bombExplosion;
		unsigned int m_bombExplosionIndex;
		std::vector<QSoundEffect*> m_bombPlaced;
		unsigned int m_bombPlacedIndex;
		std::vector<QSoundEffect*> m_gotItem;
		unsigned int m_gotItemIndex;
		QSoundEffect *m_background;
		std::vector<QSoundEffect*> m_wallDown;
		unsigned int m_wallDownIndex;
        std::vector<QSoundEffect*> m_deadPlayer;
		unsigned int m_deadPlayerIndex;
		Threading::Mutex *m_mutex;
		bool m_muted;
        double m_volume;
	};
}

#endif
