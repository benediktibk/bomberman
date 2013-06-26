#ifndef MAIN_STARTWINDOW_H
#define MAIN_STARTWINDOW_H

#include <QMainWindow>
#include "common/csvparser.h"

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

private slots:
	void exitClicked();
	void startClicked();
	void closeGameClicked();
	void levelBuildingNotCorrect();

signals:
	void startGameSignal(bool enableOpenGL, const char* levelname);
	void closeGameSignal();

private:
	void connectButtons();
	void createTableView();
	void createSilder();
	void updateSilder();

private:
	Ui::StartWindow* m_ui;
	std::string m_selectedLevel;
	Common::CSVParser m_levelList;
};
}
#endif // STARTWINDOW_H
