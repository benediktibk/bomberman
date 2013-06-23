#ifndef MAIN_STARTWINDOW_H
#define MAIN_STARTWINDOW_H

#include <QMainWindow>

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
	void connectTableView();

private:
	Ui::StartWindow* m_ui;
	std::string m_selectedLevel;
};
}
#endif // STARTWINDOW_H
