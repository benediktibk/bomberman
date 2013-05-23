#ifndef MAINWINDOWINPUTTEST_H
#define MAINWINDOWINPUTTEST_H

#include <QGraphicsScene>
#include "mainwindowinputfetcher.h"

namespace Ui
{
    class MainWindowInputTest;
}

class QLineEdit;

namespace Main
{
class MainWindowInputTest : public MainWindowInputFetcher
{
    Q_OBJECT

public:
    MainWindowInputTest();

private slots:
    void inputStateClicked();

private:
    void connectButtons();

private:
    Ui::MainWindowInputTest* m_ui;
    QLineEdit *display;
};
}



#endif // MAINWINDOWINPUTTEST_H
