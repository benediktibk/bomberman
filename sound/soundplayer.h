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
		void setMuted(bool value);
		bool isMuted() const;

	private:
		void deleteVector(std::vector<QSoundEffect*> &sounds);
		void setUpSounds(std::vector<QSoundEffect*> &sounds, const std::string &source);
		void muteSounds(std::vector<QSoundEffect*> &sounds, bool value);

	private:
		const unsigned int m_soundBufferSize;
		std::vector<QSoundEffect*> m_bombExplosion;
		unsigned int m_bombExplosionIndex;
		std::vector<QSoundEffect*> m_bombPlaced;
		unsigned int m_bombPlacedIndex;
		std::vector<QSoundEffect*> m_gotItem;
		unsigned int m_gotItemIndex;
		QSoundEffect *m_background;
		std::vector<QSoundEffect*> m_wallDown;
		unsigned int m_wallDownIndex;
		Threading::Mutex *m_mutex;
		bool m_muted;
	};
}

#endif
