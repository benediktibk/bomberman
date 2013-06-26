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
	case 3:
		drawState3();
		break;
	case 4:
		drawState4();
		break;
	default:
		break;
	}
}

void MainWindowGraphicTest::connectSlots()
{
	connect(m_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectGameState(int)));
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
	BombState *bombOne = new BombState(bombIDCreator, 0, Point(0, 2));
	BombState *bombTwo = new BombState(bombIDCreator, 0, Point(4, 1));

	gameState.addWall(wallOne);
	gameState.addWall(wallTwo);
	gameState.addWall(wallThree);
	gameState.addBomb(bombOne);
	gameState.addBomb(bombTwo);

	drawState(gameState);
}

void MainWindowGraphicTest::drawState2()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 2);
	GameState gameState(level, 3, playerIDCreator, wallIDCreator);

	drawState(gameState);
}

void MainWindowGraphicTest::drawState3()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	UniqueIdCreator powerUpIDCreator;
	LevelDefinition level;
	GameState gameState(level, 1, playerIDCreator, wallIDCreator);

	PowerUpState *powerUp = new PowerUpState(powerUpIDCreator, Point(0, 1));
	gameState.addPowerUp(powerUp);

	drawState(gameState);
}

void MainWindowGraphicTest::drawState4()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	UniqueIdCreator bombIDCreator;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	GameState gameState(level, 1, playerIDCreator, wallIDCreator);
	BombState *bomb = new BombState(bombIDCreator, 0, Point(4, 4));

	bomb->setDestructionRange(4);
	gameState.addBomb(bomb);
	gameState.reduceAllBombsLifeTime(bomb->getLifeTime()*2);
	vector<const BombState*> bombs = gameState.setAllBombsWithNoLifeTimeDestroyedAndAddExplodedBombs();
	ExplodedBombState &explodedBomb = gameState.getExplodedBombByBomb(bombs.front());
	explodedBomb.setDestructionRangeDown(2);
	explodedBomb.setDestructionRangeUp(1);
	explodedBomb.setDestructionRangeLeft(3);
	gameState.removeAllObjectsWithDestroyedFlag();

	drawState(gameState);
}

void MainWindowGraphicTest::drawState(const GameState &game)
{
	delete m_drawer;
	m_drawer = new Graphic::GraphicDrawerQt(*(m_ui->graphicsView), false);
	vector<unsigned int> playerIDs = game.getAllPossiblePlayerIDs();
	m_drawer->setResponsibleForPlayers(playerIDs);
	m_drawer->draw(game);
}
