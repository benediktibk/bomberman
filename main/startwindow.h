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
	StartWindow();

private slots:
	void exitClicked();
	void startClicked();

private:
	void connectButtons();
	void connectTableView();

private:
	Ui::StartWindow* m_ui;
	std::string m_selectedLevel;
	bool m_enableOpenGL;
};
}
#endif // STARTWINDOW_H
