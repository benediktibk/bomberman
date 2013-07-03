#include <QApplication>
#include "main/soundtestwindow.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	SoundTestWindow mainWindow;

	mainWindow.show();
	int result = a.exec();

	return result;
}
