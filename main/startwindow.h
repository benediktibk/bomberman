#ifndef MAIN_STARTWINDOW_H
#define MAIN_STARTWINDOW_H

#include <QMainWindow>
#include "common/csvparser.h"
#include "gameengine/computerenemylevel.h"

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

public slots:
	void winnerOfGame(const char* winner);

private slots:
	void exitClicked();
	void startClicked();
	void closeGameClicked();
	void levelBuildingNotCorrect();
	void showHorizontalSliderValue();
	void updateSilder();
	void readMeClicked();
	void controlClicked();

signals:
	void startGameSignal(
			bool enableOpenGL, const char* levelname,
			unsigned int humanPlayerCount, unsigned int computerEnemyCount,
			GameEngine::ComputerEnemyLevel computerEnemyLevel, bool mute);
	void closeGameSignal();

private:
	void connectButtons();
	void createTableView();
	void createSilder();
	void createComboBox();

private:
	Ui::StartWindow* m_ui;
	std::string m_selectedLevel;
	Common::CSVParser m_levelList;
};
}
#endif // STARTWINDOW_H
