#ifndef GRAPHICDRAWERQT_H
#define GRAPHICDRAWERQT_H

#include "graphicdrawer.h"

class QGraphicsScene;
class QGraphicsView;

namespace Graphic
{
class Player;
class Wall;
class Bomb;

class GraphicDrawerQt :
		public Common::GraphicDrawer
{
public:
	GraphicDrawerQt(QGraphicsView &view);
	virtual ~GraphicDrawerQt();

	virtual void draw(const Common::GameState &gameState);
	QGraphicsScene& getScene();

private:
	void drawPlayer(const Common::PlayerState &playerState);
	void drawWalls(const std::vector<Common::WallState> &walls);
	void drawBombs(const std::vector<Common::BombState> &bombs);
	void deleteWalls();
	void deleteBombs();

private:
	QGraphicsView &m_view;
	QGraphicsScene *m_scene;
	Player *m_player;
	std::vector<Wall*> m_walls;
	std::vector<Bomb*> m_bombs;
	const double m_pixelPerMeter;
};
}

#endif
