#include <QApplication>
#include "startwindow.h"

using namespace Main;

int main(int argc, char **argv)
{
	QApplication a(argc, argv);
	StartWindow startWindowTest(false);

	startWindowTest.show();
	int result = a.exec();

	return result;
}
