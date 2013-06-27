#include <QApplication>
#include "mainwindowsoundtest.h"

using namespace Main;

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindowSoundTest mainWindowSoundTest;

    mainWindowSoundTest.show();
    int result = a.exec();

    return result;
}

