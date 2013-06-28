#include "sound/soundplayer.h"
#include "threading/mutex.h"
#include "threading/lock.h"
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
	{
		Lock lock(*m_mutex);
		deleteVector(m_bombExplosion);
		deleteVector(m_bombPlaced);
		deleteVector(m_gotItem);
		deleteVector(m_wallDown);
		delete m_background;
	}

	delete m_mutex;
}

void SoundPlayer::bombExplosion()
{
	Lock lock(*m_mutex);
	m_bombExplosion[m_bombExplosionIndex];
	m_bombExplosion[m_bombExplosionIndex]->play();
	++m_bombExplosionIndex;
	if (m_bombExplosionIndex >= m_soundBufferSize)
		m_bombExplosionIndex = 0;
}

void SoundPlayer::bombPlaced()
{
	Lock lock(*m_mutex);
	m_bombPlaced[m_bombPlacedIndex]->play();
	++m_bombPlacedIndex;
	if (m_bombPlacedIndex >= m_soundBufferSize)
		m_bombPlacedIndex = 0;
}

void SoundPlayer::gotItem()
{
	Lock lock(*m_mutex);
	m_gotItem[m_gotItemIndex]->play();
	++m_gotItemIndex;
	if (m_gotItemIndex >= m_soundBufferSize)
		m_gotItemIndex = 0;
}

void SoundPlayer::wallDown()
{
	Lock lock(*m_mutex);
	m_wallDown[m_wallDownIndex]->play();
	++m_wallDownIndex;
	if (m_wallDownIndex >= m_soundBufferSize)
		m_wallDownIndex = 0;
}

void SoundPlayer::setMuted(bool value)
{
	Lock lock(*m_mutex);
	m_muted = value;
	muteSounds(m_bombExplosion, value);
	muteSounds(m_bombPlaced, value);
	muteSounds(m_gotItem, value);
	muteSounds(m_wallDown, value);
	m_background->setMuted(value);
}

bool SoundPlayer::isMuted() const
{
	Lock lock(*m_mutex);
	return m_muted;
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
