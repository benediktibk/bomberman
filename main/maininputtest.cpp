#include <QApplication>
#include "main/inputtestwindow.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	InputTestWindow inputTestWindow;

	inputTestWindow.show();
	int result = a.exec();

	return result;
}
