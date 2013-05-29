#include "mainwindowgraphictest.h"
#include "ui_mainwindowgraphictest.h"
#include "graphic/graphicdrawerqt.h"
#include "common/uniqueidcreator.h"

using namespace Main;
using namespace Common;

MainWindowGraphicTest::MainWindowGraphicTest() :
	m_ui(new Ui::MainWindowGraphicTest),
	m_drawer(0)
{
	m_ui->setupUi(this);
	m_drawer = new Graphic::GraphicDrawerQt(*(m_ui->graphicsView));

	connectSlots();
	selectGameState(0);
}

MainWindowGraphicTest::~MainWindowGraphicTest()
{
	delete m_drawer;
}

void MainWindowGraphicTest::selectGameState(int index)
{
	switch(index + 1)
	{
	case 1:
		drawState1();
		break;
	default:
		break;
	}
}

void MainWindowGraphicTest::connectSlots()
{
	connect(m_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectGameState(int)));
	connect(m_ui->comboBox, SIGNAL(highlighted(int)), this, SLOT(selectGameState(int)));
}

void MainWindowGraphicTest::drawState1()
{
    UniqueIdCreator id;
	GameState gameState;
    WallState *wallOne = new WallState(id, WallState::WallTypeSolid);
    WallState *wallTwo = new WallState(id, WallState::WallTypeSolid);
    WallState *wallThree = new WallState(id, WallState::WallTypeSolid);
    BombState *bombOne = new BombState(id);
    BombState *bombTwo = new BombState(id);

    wallOne->setPosition(Point(-3, 4));
    wallTwo->setPosition(Point(2, 3));
    wallThree->setPosition(Point(1, 5));
    bombOne->setPosition(Point(0, 2));
    bombTwo->setPosition(Point(-4, -1));
	gameState.addWall(wallOne);
	gameState.addWall(wallTwo);
	gameState.addWall(wallThree);
    gameState.addBomb(bombOne);
	gameState.addBomb(bombTwo);

	m_drawer->draw(gameState);
}
