#include "mainwindowinputtest.h"
#include "ui_mainwindowinputtest.h"
#include <QtCore/QTimer>

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindowInputTest::MainWindowInputTest() :
    m_ui(new Ui::MainWindowInputTest)
{
    m_ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(inputStateCalled()));
    m_timer->start(100);
}

void MainWindowInputTest::inputStateCalled()
{
    InputState currentInputState;
    currentInputState = getInputState();

    if (currentInputState.isDownKeyPressed())
        m_ui->inputTestDownLabel->setText(tr("Down"));
    else
        m_ui->inputTestDownLabel->setText(tr(""));

    if (currentInputState.isUpKeyPressed())
        m_ui->inputTestUpLabel->setText(tr("Up"));
    else
        m_ui->inputTestUpLabel->setText(tr(""));

    if (currentInputState.isLeftKeyPressed())
        m_ui->inputTestLeftLabel->setText(tr("Left"));
    else
        m_ui->inputTestLeftLabel->setText(tr(""));

    if (currentInputState.isRightKeyPressed())
        m_ui->inputTestRightLabel->setText(tr("Right"));
    else
        m_ui->inputTestRightLabel->setText(tr(""));

    if (currentInputState.isSpaceKeyPressed())
        m_ui->inputTestSpaceLabel->setText(tr("BOMB PLACED"));
    else
        m_ui->inputTestSpaceLabel->setText(tr(""));
}
