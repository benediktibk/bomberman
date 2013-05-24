#include "mainwindowinputtest.h"
#include "ui_mainwindowinputtest.h"

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindowInputTest::MainWindowInputTest() :
    m_ui(new Ui::MainWindowInputTest)
{
    m_ui->setupUi(this);
    m_inputTest = m_ui->displayLineEdit;

    m_inputTest->setText(tr(""));

    connectButtons();
}

void MainWindowInputTest::connectButtons()
{
    connect(m_ui->inputStateButton, SIGNAL(clicked()), this, SLOT(inputStateClicked()));
}

void MainWindowInputTest::inputStateClicked()
{
    InputState currentInputState;
    currentInputState = getInputState();

    if (currentInputState.isDownKeyPressed())
        m_inputTest->setText(tr("Down"));
    else
        m_inputTest->setText(tr("Nothing"));
}
