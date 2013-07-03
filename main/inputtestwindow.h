#ifndef MAIN_INPUTTESTWINDOW_H
#define MAIN_INPUTTESTWINDOW_H

#include "main/inputfetcherwindow.h"

namespace Ui
{
	class InputTestWindow;
}

class QTimer;

namespace Main
{
	class InputTestWindow :
			public InputFetcherWindow
	{
		Q_OBJECT

	public:
		InputTestWindow();

	private slots:
		void inputStateCalled();

	private:
		Ui::InputTestWindow* m_ui;
		QTimer *m_timer;
	};
}

#endif
