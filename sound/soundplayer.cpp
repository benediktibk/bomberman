#include "sound/soundplayer.h"
#include <QtMultimedia/QSoundEffect>

using namespace Sound;
using namespace std;

SoundPlayer::SoundPlayer()
{}

SoundPlayer::~SoundPlayer()
{
    deleteVector(m_bombExplosion);
    deleteVector(m_bombPlaced);
    deleteVector(m_gotItem);
}

void SoundPlayer::bombExplosion()
{
    QSoundEffect *sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile("resources/sounds/bomb.wav"));
    removeFinishedSounds(m_bombExplosion);
    m_bombExplosion.push_back(sound);
    sound->play();
}

void SoundPlayer::bombPlaced()
{
    QSoundEffect *sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile("resources/sounds/placed.wav"));
    removeFinishedSounds(m_bombPlaced);
    m_bombPlaced.push_back(sound);
    sound->play();
}

void SoundPlayer::gotItem()
{
    QSoundEffect *sound = new QSoundEffect;
    sound->setSource(QUrl::fromLocalFile("resources/sounds/gotitem.wav"));
    removeFinishedSounds(m_gotItem);
    m_gotItem.push_back(sound);
    sound->play();
}

void SoundPlayer::removeFinishedSounds(vector<QSoundEffect*> &sounds)
{
    size_t i = 0;
	while (i < sounds.size())
	{
        if (!sounds[i]->isPlaying())
        {   
            delete sounds[i];
			sounds.erase(sounds.begin()+i);
        }
		else
			i++;
	}
}

void SoundPlayer::deleteVector(vector<QSoundEffect*> &sounds)
{
    for(vector<QSoundEffect*>::iterator i = sounds.begin();i != sounds.end(); ++i)
    {
        delete *i;
    }
    sounds.clear();
}
