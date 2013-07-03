#include "main/gamewindow.h"
#include "main/userinputsimulator.h"
#include <QApplication>
#include <QtCore/QObject>

int main(int argc, char **argv)
{
	QApplication application(argc, argv);
	Main::UserInputSimulator userInputSimulator;
	userInputSimulator.show();
	return application.exec();
}
