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
    std::vector<unsigned int> allPlayerIds(2);
    allPlayerIds[0] = 0;
    allPlayerIds[1] = 1;

    setAllPossiblePlayerIDs(allPlayerIds);
    std::map<unsigned int, InputState> currentInputState;
    currentInputState = getInputStates();

    if (currentInputState[0].isDownKeyPressed())
        m_ui->inputTestDownLabel->setText(tr("Down"));
    else if (currentInputState[1].isDownKeyPressed())
        m_ui->inputTestDownLabel->setText(tr("S"));
    else
        m_ui->inputTestDownLabel->setText(tr(""));

    if (currentInputState[0].isUpKeyPressed())
        m_ui->inputTestUpLabel->setText(tr("Up"));
    else if (currentInputState[1].isUpKeyPressed())
        m_ui->inputTestUpLabel->setText(tr("W"));
    else
        m_ui->inputTestUpLabel->setText(tr(""));

    if (currentInputState[0].isLeftKeyPressed())
        m_ui->inputTestLeftLabel->setText(tr("Left"));
    else if (currentInputState[1].isLeftKeyPressed())
        m_ui->inputTestLeftLabel->setText(tr("A"));
    else
        m_ui->inputTestLeftLabel->setText(tr(""));

    if (currentInputState[0].isRightKeyPressed())
        m_ui->inputTestRightLabel->setText(tr("Right"));
    else if (currentInputState[1].isRightKeyPressed())
        m_ui->inputTestRightLabel->setText(tr("D"));
    else
        m_ui->inputTestRightLabel->setText(tr(""));

    if (currentInputState[0].isSpaceKeyPressed())
        m_ui->inputTestSpaceLabel->setText(tr("BOMB PLACED"));
    else if (currentInputState[1].isSpaceKeyPressed())
        m_ui->inputTestSpaceLabel->setText(tr("BOMB PLACED Player 2"));
    else
        m_ui->inputTestSpaceLabel->setText(tr(""));
}
