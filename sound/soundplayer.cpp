#include "sound/soundplayer.h"
#include "threading/mutex.h"
#include <QtMultimedia/QSoundEffect>

using namespace Sound;
using namespace Threading;
using namespace std;

SoundPlayer::SoundPlayer(bool mute) :
	m_soundBufferSize(10),
	m_bombExplosionIndex(0),
	m_bombPlacedIndex(0),
	m_gotItemIndex(0),
	m_background(new QSoundEffect),
	m_wallDownIndex(0),
	m_mutex(new Mutex),
	m_muted(mute)
{
	setUpSounds(m_bombExplosion, "resources/sounds/bomb.wav");
	setUpSounds(m_bombPlaced, "resources/sounds/placed.wav");
	setUpSounds(m_gotItem, "resources/sounds/gotitem.wav");
	setUpSounds(m_wallDown, "resources/sounds/walldown.wav");
	m_background->setSource(QUrl::fromLocalFile("resources/sounds/background.wav"));
	m_background->setLoopCount(QSoundEffect::Infinite);
	m_background->play();
	setMuted(m_muted);
}

SoundPlayer::~SoundPlayer()
{
	m_mutex->lock();
	deleteVector(m_bombExplosion);
	deleteVector(m_bombPlaced);
	deleteVector(m_gotItem);
	deleteVector(m_wallDown);
	delete m_background;
	m_mutex->unlock();
	delete m_mutex;
}

void SoundPlayer::bombExplosion()
{
	m_mutex->lock();
	m_bombExplosion[m_bombExplosionIndex];
	m_bombExplosion[m_bombExplosionIndex]->play();
	++m_bombExplosionIndex;
	if (m_bombExplosionIndex >= m_soundBufferSize)
		m_bombExplosionIndex = 0;
	m_mutex->unlock();
}

void SoundPlayer::bombPlaced()
{
	m_mutex->lock();
	m_bombPlaced[m_bombPlacedIndex]->play();
	++m_bombPlacedIndex;
	if (m_bombPlacedIndex >= m_soundBufferSize)
		m_bombPlacedIndex = 0;
	m_mutex->unlock();
}

void SoundPlayer::gotItem()
{
	m_mutex->lock();
	m_gotItem[m_gotItemIndex]->play();
	++m_gotItemIndex;
	if (m_gotItemIndex >= m_soundBufferSize)
		m_gotItemIndex = 0;
	m_mutex->unlock();
}

void SoundPlayer::wallDown()
{
	m_mutex->lock();
	m_wallDown[m_wallDownIndex]->play();
	++m_wallDownIndex;
	if (m_wallDownIndex >= m_soundBufferSize)
		m_wallDownIndex = 0;
	m_mutex->unlock();
}

void SoundPlayer::setMuted(bool value)
{
	m_mutex->lock();
	m_muted = value;
	muteSounds(m_bombExplosion, value);
	muteSounds(m_bombPlaced, value);
	muteSounds(m_gotItem, value);
	muteSounds(m_wallDown, value);
	m_background->setMuted(value);
	m_mutex->unlock();
}

bool SoundPlayer::isMuted() const
{
	m_mutex->lock();
	bool result = m_muted;
	m_mutex->unlock();
	return result;
}

void SoundPlayer::deleteVector(vector<QSoundEffect*> &sounds)
{
	for(vector<QSoundEffect*>::iterator i = sounds.begin();i != sounds.end(); ++i)
		delete *i;
	sounds.clear();
}

void SoundPlayer::setUpSounds(vector<QSoundEffect*> &sounds, const std::string &source)
{
	sounds.clear();

	for(unsigned int i = 0; i < m_soundBufferSize; ++i)
	{
		QSoundEffect *sound = new QSoundEffect();
		sound->setSource(QUrl::fromLocalFile(source.c_str()));
		sounds.push_back(sound);
	}
}

void SoundPlayer::muteSounds(vector<QSoundEffect*> &sounds, bool value)
{
	for (vector<QSoundEffect*>::iterator i = sounds.begin(); i != sounds.end(); ++i)
		(*i)->setMuted(value);
}
