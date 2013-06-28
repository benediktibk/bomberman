#include "sound/soundplayer.h"
#include <QtMultimedia/QSoundEffect>

using namespace Sound;
using namespace std;

SoundPlayer::SoundPlayer() :
    m_soundBufferSize(10),
    m_bombExplosionIndex(0),
    m_bombPlacedIndex(0),
    m_gotItemIndex(0),
    m_background(new QSoundEffect)
{
    setUpSounds(m_bombExplosion, "resources/sounds/bomb.wav");
    setUpSounds(m_bombPlaced, "resources/sounds/placed.wav");
    setUpSounds(m_gotItem, "resources/sounds/gotitem.wav");
    m_background->setSource(QUrl::fromLocalFile("resources/sounds/background.wav"));
    m_background->setLoopCount(QSoundEffect::Infinite);
    m_background->play();
}

SoundPlayer::~SoundPlayer()
{
    deleteVector(m_bombExplosion);
    deleteVector(m_bombPlaced);
    deleteVector(m_gotItem);
    delete m_background;
}

void SoundPlayer::bombExplosion()
{   
    m_bombExplosion[m_bombExplosionIndex];
    m_bombExplosion[m_bombExplosionIndex]->play();
    ++m_bombExplosionIndex;
    if (m_bombExplosionIndex >= m_soundBufferSize)
        m_bombExplosionIndex = 0;
}

void SoundPlayer::bombPlaced()
{
    m_bombPlaced[m_bombPlacedIndex]->play();
    ++m_bombPlacedIndex;
    if (m_bombPlacedIndex >= m_soundBufferSize)
        m_bombPlacedIndex = 0;
}

void SoundPlayer::gotItem()
{
    m_gotItem[m_gotItemIndex]->play();
    ++m_gotItemIndex;
    if (m_gotItemIndex >= m_soundBufferSize)
        m_gotItemIndex = 0;
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
