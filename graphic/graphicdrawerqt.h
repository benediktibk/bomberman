#ifndef GRAPHIC_GRAPHICDRAWERQT_H
#define GRAPHIC_GRAPHICDRAWERQT_H

#include <map>
#include "common/graphicdrawer.h"
#include "common/compare.h"
#include <QtCore/QRectF>

class QGraphicsScene;
class QGraphicsView;
class QBrush;

namespace Graphic
{
	class SvgRenderer;
	class Player;
	class Wall;
	class Bomb;
	class PowerUp;
	class ExplodedBomb;

	class GraphicDrawerQt :
			public Common::GraphicDrawer
	{
	public:
		GraphicDrawerQt(const std::vector<QGraphicsView*> &views, bool enableOpenGL);
		virtual ~GraphicDrawerQt();

		virtual void setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs);
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
		void drawExplodedBombs(const std::vector<const Common::ExplodedBombState*> &explodedBombs);
		void drawExplodedBomb(const Common::ExplodedBombState *explodedBomb);
		void setSceneRectForViews();
		void fitWholeAreaInView(QGraphicsView &view);
		void updateViewPositionForPlayer(const Common::PlayerState &player, QGraphicsView &view);
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
		void deleteExplodedBombs();
		void deleteWall(const Common::WallState *wall);
		void deleteBomb(const Common::BombState *bomb);
		void deletePowerUp(const Common::PowerUpState *powerUp);
		void deleteExplodedBomb(const Common::ExplodedBombState *explodedBomb);
		void deleteBorderWalls();
		void deletePlayers();
		QRectF calculateSceneRect(const Common::GameState &gameState);
		void scale(double factor, QGraphicsView &view);
		void setScaleOfAllViewsToOne();
		void configureView(QGraphicsView &view, bool enableOpenGL);
		void configureViews(bool enableOpenGL);
		void createBackgroundBrush();
		void updateViewPorts();
		void updateViewAreas(const Common::GameState &gameState);
		void updateViewArea(unsigned int playerID, QGraphicsView &view, const Common::GameState &gameState);
		void initializeScales();

	private:
		std::vector<QGraphicsView*> m_views;
		std::map<unsigned int, QGraphicsView*> m_playerIDToViewMap;
		std::map<QGraphicsView*, double> m_currentScales;
		QGraphicsScene *m_scene;
		std::map<const Common::PlayerState*, Player*> m_players;
		std::map<const Common::WallState*, Wall*> m_walls;
		std::map<const Common::BombState*, Bomb*> m_bombs;
		std::map<const Common::PowerUpState*, PowerUp*> m_powerUps;
		std::map<const Common::ExplodedBombState*, ExplodedBomb*> m_explodedBombs;
		const double m_pixelPerMeter;
		bool m_firstRedraw;
		std::vector<Wall*> m_borderWalls;
		const double m_minimumViewDistance;
		const double m_minimumViewDistanceInPixel;
		bool m_responsibilityValid;
		SvgRenderer *m_svgRenderer;
		QBrush *m_backgroundBrush;
		QRectF m_sceneRect;
		Common::Compare m_scaleCompare;
		Common::Compare m_viewAreaCompare;
	};
}

#endif
