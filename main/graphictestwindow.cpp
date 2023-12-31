#include "main/graphictestwindow.h"
#include "ui_graphictestwindow.h"
#include "graphic/graphicdrawerqt.h"
#include "common/uniqueidcreator.h"
#include "common/leveldefinition.h"

using namespace Main;
using namespace Common;
using namespace std;

GraphicTestWindow::GraphicTestWindow() :
	m_ui(new Ui::GraphicTestWindow),
	m_drawer(0)
{
	m_ui->setupUi(this);

	connectSlots();
	selectGameState(0);
}

GraphicTestWindow::~GraphicTestWindow()
{
	delete m_drawer;
}

void GraphicTestWindow::selectGameState(int index)
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

void GraphicTestWindow::connectSlots()
{
	connect(m_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectGameState(int)));
}

void GraphicTestWindow::drawState1()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	UniqueIdCreator bombIDCreator;
	LevelDefinition level;
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	GameState gameState(level, 1, 0, playerIDCreator, wallIDCreator);
	WallState *wallOne = new WallState(wallIDCreator, WallState::WallTypeSolid, Point(3, 4));
	WallState *wallTwo = new WallState(wallIDCreator, WallState::WallTypeSolid, Point(2, 3));
	WallState *wallThree = new WallState(wallIDCreator, WallState::WallTypeLoose, Point(1, 5));
	BombState *bombOne = new BombState(bombIDCreator, 0, Point(0, 2), 1);
	BombState *bombTwo = new BombState(bombIDCreator, 0, Point(4, 1), 1);

	gameState.addWall(wallOne);
	gameState.addWall(wallTwo);
	gameState.addWall(wallThree);
	gameState.addBomb(bombOne);
	gameState.addBomb(bombTwo);

	drawState(gameState);
}

void GraphicTestWindow::drawState2()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 1, 1);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 2, 2);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 4, 4);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 5, 5);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 6, 6);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 7, 7);
	GameState gameState(level, 3, 4, playerIDCreator, wallIDCreator);

	drawState(gameState);
}

void GraphicTestWindow::drawState3()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	UniqueIdCreator powerUpIDCreator;
	LevelDefinition level;
	GameState gameState(level, 1, 0, playerIDCreator, wallIDCreator);

	PowerUpState *powerUp = new PowerUpState(powerUpIDCreator, Point(0, 1));
	gameState.addPowerUp(powerUp);

	drawState(gameState);
}

void GraphicTestWindow::drawState4()
{
	UniqueIdCreator wallIDCreator;
	UniqueIdCreator playerIDCreator;
	UniqueIdCreator bombIDCreator;
	LevelDefinition level(10, 10);
	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 0, 0);
	GameState gameState(level, 1, 0, playerIDCreator, wallIDCreator);
	BombState *bomb = new BombState(bombIDCreator, 0, Point(4, 4), 4);

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

void GraphicTestWindow::drawState(const GameState &game)
{
	delete m_drawer;
	vector<QGraphicsView*> views;
	views.push_back(m_ui->graphicsView);
	m_drawer = new Graphic::GraphicDrawerQt(views, false);
	vector<unsigned int> playerIDs = game.getAllNotDestroyedPlayerIDs();
	vector<unsigned int> firstPlayerID;
	firstPlayerID.push_back(playerIDs.front());
	m_drawer->setResponsibleForPlayers(firstPlayerID);
	m_drawer->draw(game);
}
