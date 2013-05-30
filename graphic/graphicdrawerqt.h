#ifndef GRAPHIC_GRAPHICDRAWERQT_H
#define GRAPHIC_GRAPHICDRAWERQT_H

#include <map>
#include "common/graphicdrawer.h"

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
	void drawWalls(const std::vector<const Common::WallState*> &walls);
	void drawWall(const Common::WallState *wall);
	void drawBombs(const std::vector<const Common::BombState*> &bombs);
	void drawBomb(const Common::BombState *bomb);
	void drawBorderWalls(unsigned int width, unsigned int height);
	void drawLeftBorderWalls(unsigned int height);
	void drawRightBorderWalls(unsigned int width, unsigned int height);
	void drawUpperBorderWalls(unsigned int width, unsigned int height);
	void drawLowerBorderWalls(unsigned int width);
	void drawEdgeBorderWalls(unsigned int width, unsigned int height);
	void deleteWalls();
	void deleteBombs();
	void deleteWall(const Common::WallState *wall);
	void deleteBomb(const Common::BombState *bomb);
	void deleteBorderWalls();

private:
	QGraphicsView &m_view;
	QGraphicsScene *m_scene;
	Player *m_player;
	std::map<const Common::WallState*, Wall*> m_walls;
	std::map<const Common::BombState*, Bomb*> m_bombs;
	const double m_pixelPerMeter;
	bool m_firstRedraw;
	std::vector<Wall*> m_borderWalls;
};
}

#endif
