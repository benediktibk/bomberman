#include "graphicdrawerqt.h"
#include "player.h"
#include "wall.h"
#include "bomb.h"
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace Graphic;
using namespace Common;
using namespace std;

GraphicDrawerQt::GraphicDrawerQt(QGraphicsView &view) :
	m_view(view),
	m_scene(new QGraphicsScene()),
	m_player(new Player(*m_scene)),
	m_pixelPerMeter(40),
	m_firstRedraw(true)
{
	m_scene->setSceneRect(-100, -100, 200, 200);
	m_view.setBackgroundBrush(QBrush(QColor(255, 255, 255)));
	m_view.setScene(m_scene);
}

GraphicDrawerQt::~GraphicDrawerQt()
{
	deleteWalls();
	deleteBombs();
	deleteBorderWalls();
	delete m_player;
	delete m_scene;
}

void GraphicDrawerQt::draw(const GameState &gameState)
{
	if (m_firstRedraw)
		drawBorderWalls(gameState.getGameStateWidth(), gameState.getGameStateHeight());

	drawWalls(gameState.getAllChangedWalls());
	drawBombs(gameState.getAllChangedBombs());
	drawPlayer(gameState.getFirstPlayerState());
	m_firstRedraw = false;
}

QGraphicsScene &GraphicDrawerQt::getScene()
{
	return *m_scene;
}

void GraphicDrawerQt::drawPlayer(const PlayerState &playerState)
{
	m_player->update(playerState, m_pixelPerMeter);
}

void GraphicDrawerQt::drawWalls(const vector<const WallState*> &walls)
{
	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
		drawWall(*i);
}

void GraphicDrawerQt::drawWall(const WallState *wallState)
{
	if (wallState->isDestroyed())
		deleteWall(wallState);
	else
	{
		map<const WallState*, Wall*>::iterator wallPosition = m_walls.find(wallState);
		bool wallFound = wallPosition != m_walls.end();
		Wall* wall = 0;

		if (!wallFound)
			wall = new Wall(*m_scene, *wallState);
		else
			wall = wallPosition->second;

		wall->update(*wallState, m_pixelPerMeter);

		if (!wallFound)
			m_walls.insert(pair<const WallState*, Wall*>(wallState, wall));
	}
}

void GraphicDrawerQt::drawBombs(const vector<const BombState*> &bombs)
{
	for (vector<const BombState*>::const_iterator i = bombs.begin(); i != bombs.end(); ++i)
		drawBomb(*i);
}

void GraphicDrawerQt::drawBomb(const BombState *bombState)
{
	if (bombState->isDestroyed())
		deleteBomb(bombState);
	else
	{
		map<const BombState*, Bomb*>::iterator bombPosition = m_bombs.find(bombState);
		bool bombFound = bombPosition != m_bombs.end();
		Bomb* bomb = 0;

		if (!bombFound)
			bomb = new Bomb(*m_scene);
		else
			bomb = bombPosition->second;

		bomb->update(*bombState, m_pixelPerMeter);

		if (!bombFound)
			m_bombs.insert(pair<const BombState*, Bomb*>(bombState, bomb));
	}
}

void GraphicDrawerQt::drawBorderWalls(unsigned int width, unsigned int height)
{
	drawLeftBorderWalls(height);
	drawRightBorderWalls(width, height);
	drawLowerBorderWalls(width);
	drawUpperBorderWalls(width, height);
	drawEdgeBorderWalls(width, height);
}

void GraphicDrawerQt::drawLeftBorderWalls(unsigned int height)
{
	for (unsigned int y = 0; y < height; ++y)
		m_borderWalls.push_back(new Wall(*m_scene, Point(-1, y), m_pixelPerMeter));
}

void GraphicDrawerQt::drawRightBorderWalls(unsigned int width, unsigned int height)
{
	for (unsigned int y = 0; y < height; ++y)
		m_borderWalls.push_back(new Wall(*m_scene, Point(width, y), m_pixelPerMeter));
}

void GraphicDrawerQt::drawUpperBorderWalls(unsigned int width, unsigned int height)
{
	for (unsigned int x = 0; x < width; ++x)
		m_borderWalls.push_back(new Wall(*m_scene, Point(x, height), m_pixelPerMeter));
}

void GraphicDrawerQt::drawLowerBorderWalls(unsigned int width)
{
	for (unsigned int x = 0; x < width; ++x)
		m_borderWalls.push_back(new Wall(*m_scene, Point(x, -1), m_pixelPerMeter));
}

void GraphicDrawerQt::drawEdgeBorderWalls(unsigned int width, unsigned int height)
{
	m_borderWalls.push_back(new Wall(*m_scene, Point(-1, -1), m_pixelPerMeter));
    m_borderWalls.push_back(new Wall(*m_scene, Point(-1, height), m_pixelPerMeter));
	m_borderWalls.push_back(new Wall(*m_scene, Point(width, -1), m_pixelPerMeter));
    m_borderWalls.push_back(new Wall(*m_scene, Point(width, height), m_pixelPerMeter));
}

void GraphicDrawerQt::deleteWalls()
{
	for (map<const WallState*, Wall*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		delete i->second;

	m_walls.clear();
}

void GraphicDrawerQt::deleteBombs()
{
	for (map<const BombState*, Bomb*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		delete i->second;

	m_bombs.clear();
}

void GraphicDrawerQt::deleteWall(const WallState *wall)
{
	map<const WallState*, Wall*>::iterator position = m_walls.find(wall);
	delete position->second;
	m_walls.erase(position);
}

void GraphicDrawerQt::deleteBomb(const BombState *bomb)
{
	map<const BombState*, Bomb*>::iterator position = m_bombs.find(bomb);
	delete position->second;
	m_bombs.erase(position);
}

void GraphicDrawerQt::deleteBorderWalls()
{
	for (vector<Wall*>::iterator i = m_borderWalls.begin(); i != m_borderWalls.end(); ++i)
		delete *i;

	m_borderWalls.clear();
}
