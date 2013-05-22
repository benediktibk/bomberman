#include <QApplication>
#include "mainwindowinputtest.h"

using namespace Main;

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindowInputTest mainWindowInputTest;

    mainWindowInputTest.show();
    int result = a.exec();

    return result;
}
