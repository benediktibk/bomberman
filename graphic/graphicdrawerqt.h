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
	class PowerUp;

	class GraphicDrawerQt :
			public Common::GraphicDrawer
	{
	public:
		GraphicDrawerQt(QGraphicsView &view);
		virtual ~GraphicDrawerQt();

		virtual void draw(const Common::GameState &gameState);
		QGraphicsScene& getScene();

	private:
		void drawPlayers(const Common::GameState &gameState);
		void drawPlayer(const Common::PlayerState *playerState);
		void drawWalls(const std::vector<const Common::WallState*> &walls);
		void drawWall(const Common::WallState *wall);
		void drawBombs(const std::vector<const Common::BombState*> &bombs);
		void drawBomb(const Common::BombState *bomb);
		void drawPowerUps(const std::vector<const Common::PowerUpState*> &powerUps);
		void drawPowerUp(const Common::PowerUpState *powerUp);
		void updateViewArea(const Common::GameState &gameState);
		void updateViewPositionForPlayer(const Common::PlayerState &player);
		void setViewPositionToTheCenterOfPlayer(const Common::PlayerState &player);
		void drawBorderWalls(unsigned int width, unsigned int height);
		void drawLeftBorderWalls(unsigned int height);
		void drawRightBorderWalls(unsigned int width, unsigned int height);
		void drawUpperBorderWalls(unsigned int width, unsigned int height);
		void drawLowerBorderWalls(unsigned int width);
		void drawEdgeBorderWalls(unsigned int width, unsigned int height);
		void deleteWalls();
		void deleteBombs();
		void deletePowerUps();
		void deleteWall(const Common::WallState *wall);
		void deleteBomb(const Common::BombState *bomb);
		void deletePowerUp(const Common::PowerUpState *powerUp);
		void deleteBorderWalls();
		void deletePlayers();

	private:
		QGraphicsView &m_view;
		QGraphicsScene *m_scene;
		std::map<const Common::PlayerState*, Player*> m_players;
		std::map<const Common::WallState*, Wall*> m_walls;
		std::map<const Common::BombState*, Bomb*> m_bombs;
		std::map<const Common::PowerUpState*, PowerUp*> m_powerUps;
		const double m_pixelPerMeter;
		bool m_firstRedraw;
		std::vector<Wall*> m_borderWalls;
		const double m_minimumViewDistance;
		const double m_minimumViewDistanceInPixel;
	};
}

#endif
