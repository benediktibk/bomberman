#ifndef MAIN_STARTWINDOW_H
#define MAIN_STARTWINDOW_H

#include <QMainWindow>
#include "common/csvparser.h"
#include "gameengine/computerenemylevel.h"
#include "common/winnertype.h"

namespace Ui
{
	class StartWindow;
}

class QGraphicsView;

namespace Main
{
	class StartWindow :
			public QMainWindow
	{
		Q_OBJECT

	public:
		StartWindow(bool enableOpenGL);
		virtual ~StartWindow();

	public slots:
		void winnerOfGame(int winner);

	private slots:
		void exitClicked();
		void startClicked();
		void setSoundSettings(bool oldMute, int oldVoulume);
		void levelBuildingNotCorrect();
		void showHorizontalSliderValue();
		void updateSilder();
		void readMeClicked();
		void controlClicked();

	signals:
		void startGameSignal(
				bool enableOpenGL, const char* levelname,
				unsigned int humanPlayerCount, unsigned int computerEnemyCount,
				GameEngine::ComputerEnemyLevel computerEnemyLevel, bool mute, double volume);
		void closeGameSignal();

	private:
		void connectButtons();
		void createTableView();
		void createSilders();
		void createComboBox();

	private:
		Ui::StartWindow* m_ui;
		std::string m_selectedLevel;
		Common::CSVParser m_levelList;
	};
}

#endif
