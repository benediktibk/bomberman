#ifndef MAIN_SOUNDTESTWINDOW_H
#define MAIN_SOUNDTESTWINDOW_H

#include <QMainWindow>

namespace Sound
{
	class SoundPlayer;
}

namespace Ui
{
	class SoundTestWindow;
}

namespace Main
{
	class SoundTestWindow :
			public QMainWindow
	{
		Q_OBJECT

	public:
		SoundTestWindow();
		~SoundTestWindow();

	private:
		void connectSlots();

	private slots:
		void bombExplosion();
		void bombPlaced();
		void gotItem();
		void wallDown();
		void deadPlayer();
		void muteChanged();

	private:
		Ui::SoundTestWindow* m_ui;
		Sound::SoundPlayer *m_sound;
	};
}

#endif
