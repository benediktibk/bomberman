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
	m_pixelPerMeter(40)
{
	m_scene->setSceneRect(-100, -100, 200, 200);
	m_view.setBackgroundBrush(QBrush(QColor(255, 255, 255)));
	m_view.setScene(m_scene);
}

GraphicDrawerQt::~GraphicDrawerQt()
{
	deleteWalls();
	deleteBombs();
	delete m_player;
	delete m_scene;
}

void GraphicDrawerQt::draw(const GameState &gameState)
{
	drawWalls(gameState.getAllChangedWalls());
	drawBombs(gameState.getAllChangedBombs());
	drawPlayer(gameState.getPlayerState());
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
	deleteWalls();

	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
	{
        const WallState &state = **i;
        Wall* wall = new Wall(*m_scene, state);
		wall->update(state, m_pixelPerMeter);
		m_walls.push_back(wall);
	}
}

void GraphicDrawerQt::drawBombs(const vector<const BombState *> &bombs)
{
	deleteBombs();

	for (vector<const BombState*>::const_iterator i = bombs.begin(); i != bombs.end(); ++i)
	{
		Bomb* bomb = new Bomb(*m_scene);
		const BombState &state = **i;
		bomb->update(state, m_pixelPerMeter);
		m_bombs.push_back(bomb);
	}
}

void GraphicDrawerQt::deleteWalls()
{
	for (vector<Wall*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		delete *i;

	m_walls.clear();
}

void GraphicDrawerQt::deleteBombs()
{
	for (vector<Bomb*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		delete *i;

	m_bombs.clear();
}
