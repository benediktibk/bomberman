#ifndef MAIN_SPLASHSCREEN_H
#define MAIN_SPLASHSCREEN_H

#include <QMainWindow>

class QTimer;

namespace Ui
{
	class SplashScreen;
}

namespace Main
{
	class SplashScreen :
			public QMainWindow
	{
		Q_OBJECT

	public:
		SplashScreen();
		~SplashScreen();

	signals:
		void closed();

	protected:
		virtual void keyPressEvent(QKeyEvent *event);

	private slots:
		void timeout();

	private:
		void setBackgroundImage();
		void moveToCenterOfScreen();
		void setLabelColor();

	private:
		Ui::SplashScreen* m_ui;
		QTimer *m_closeTimer;
	};
}

#endif
