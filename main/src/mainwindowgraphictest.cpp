#include "mainwindowgraphictest.h"
#include "ui_mainwindowgraphictest.h"
#include "graphicdrawerqt.h"

using namespace Main;

MainWindowGraphicTest::MainWindowGraphicTest() :
	m_ui(new Ui::MainWindowGraphicTest),
	m_drawer(0)
{
	m_ui->setupUi(this);
	m_drawer = new Graphic::GraphicDrawerQt(*(m_ui->graphicsView));
}

MainWindowGraphicTest::~MainWindowGraphicTest()
{
	delete m_drawer;
}
