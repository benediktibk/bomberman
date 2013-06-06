#include "mainwindowgraphictest.h"
#include "ui_mainwindowgraphictest.h"
#include "graphic/graphicdrawerqt.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"

using namespace Main;
using namespace Common;
using namespace std;

MainWindowGraphicTest::MainWindowGraphicTest() :
	m_ui(new Ui::MainWindowGraphicTest),
	m_drawer(0)
{
	m_ui->setupUi(this);

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
	case 2:
		drawState2();
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
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	UniqueIdCreator bombIDCreator;
	LevelDefinition level;
	GameState gameState(level, 1, playerIDCreator, wallIDCreator);
	WallState *wallOne = new WallState(wallIDCreator, WallState::WallTypeSolid, Point(3, 4));
	WallState *wallTwo = new WallState(wallIDCreator, WallState::WallTypeSolid, Point(2, 3));
	WallState *wallThree = new WallState(wallIDCreator, WallState::WallTypeLoose, Point(1, 5));
	BombState *bombOne = new BombState(bombIDCreator);
	BombState *bombTwo = new BombState(bombIDCreator);

	bombOne->setPosition(Point(0, 2));
	bombTwo->setPosition(Point(4, 1));
	gameState.addWall(wallOne);
	gameState.addWall(wallTwo);
	gameState.addWall(wallThree);
	gameState.addBomb(bombOne);
	gameState.addBomb(bombTwo);

	delete m_drawer;
	m_drawer = new Graphic::GraphicDrawerQt(*(m_ui->graphicsView));
	m_drawer->draw(gameState);
}

void MainWindowGraphicTest::drawState2()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	LevelDefinition level;
	GameState gameState(level, 3, playerIDCreator, wallIDCreator);
	vector<unsigned int> playerIDs = gameState.getAllPossiblePlayerIDs();

	for (unsigned int i = 0; i < playerIDs.size(); ++i)
	{
		unsigned int playerID = playerIDs[i];
		PlayerState& player = gameState.getPlayerStateById(playerID);
		player.setPosition(Point(i, i));
	}

	delete m_drawer;
	m_drawer = new Graphic::GraphicDrawerQt(*(m_ui->graphicsView));
	m_drawer->draw(gameState);
}
