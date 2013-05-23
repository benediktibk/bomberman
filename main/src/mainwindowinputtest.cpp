#include "mainwindowinputtest.h"
#include "ui_mainwindowinputtest.h"

using namespace Common;
using namespace Main;
using namespace Qt;

MainWindowInputTest::MainWindowInputTest() :
    m_ui(new Ui::MainWindowInputTest)
{
    m_ui->setupUi(this);
    display = m_ui->displayLineEdit;

    display->setText(tr("0"));

    connectButtons();
}

void MainWindowInputTest::connectButtons()
{
    connect(m_ui->inputStateButton, SIGNAL(clicked()), this, SLOT(inputStateClicked()));
}

void MainWindowInputTest::inputStateClicked()
{

}
