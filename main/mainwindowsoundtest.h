#ifndef MAIN_MAINWINDOWSOUNDTEST_H
#define MAIN_MAINWINDOWSOUNDTEST_H

#include <QMainWindow>

namespace Sound 
{
    class SoundPlayer;
}

namespace Ui
{
	class MainWindowSoundTest;
}

namespace Main 
{
    class MainWindowSoundTest : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindowSoundTest();
        ~MainWindowSoundTest();
        
    private:
        void connectSlots();
        
    private slots:
        void bombExplosion();
    
    private:
        Ui::MainWindowSoundTest* m_ui;
        Sound::SoundPlayer *m_sound;
    };
}

#endif
