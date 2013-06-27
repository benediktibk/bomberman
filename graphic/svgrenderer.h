#ifndef GRAPHIC_SVGRENDERER_H
#define GRAPHIC_SVGRENDERER_H

#include "common/powerupstate.h"
#include <vector>
#include <string>

class QGraphicsItem;
class QPixmap;

namespace Common
{
	class GameState;
}

namespace Graphic
{
	class SvgRenderer
	{
	public:
		SvgRenderer(const double pixelPerMeter, const Common::GameState &gameState);
		~SvgRenderer();

		QGraphicsItem* getNewPlayerStandingItem(unsigned int playerID, double dimension);
		QGraphicsItem* getNewPlayerMovingLeftItem(unsigned int playerId, double dimension);
		QGraphicsItem* getNewPlayerMovingUpItem(unsigned int playerId, double dimension);
		QGraphicsItem* getNewPlayerMovingRightItem(unsigned int playerId, double dimension);
		QGraphicsItem* getNewPlayerMovingDownItem(unsigned int playerId, double dimension);
		QGraphicsItem* getNewBombItem(double dimension);
		QGraphicsItem* getNewSolidWallItem(double dimension);
		QGraphicsItem* getNewLooseWallItem(double dimension);
		QGraphicsItem* getNewPowerUpItem(Common::PowerUpType powerUpType, double dimension);
		QGraphicsItem* getNewExplodedBombCenterItem(double dimension);
		QGraphicsItem* getNewExplodedBombFlameItem(double dimension);
		QGraphicsItem* getNewExplodedBombEndItem(double dimension);

	private:
		void renderPlayerItems();
		void renderBombItem();
		void renderWallItems();
		void renderPowerUpItems();
		void renderExplodedBombItems();
		void clearPixmapList(std::vector<QPixmap*> &list);
		QGraphicsItem* getNewGraphicsItemFromRenderer(const std::vector<QPixmap*> &list, unsigned int index, double dimension) const;
		QPixmap* createPixmapFromSvg(const std::string &file) const;

	private:
		const double m_pixelPerMeter;
		const Common::GameState &m_gameState;
		std::vector<QPixmap*> m_humanPlayerStanding;
		std::vector<QPixmap*> m_computerEnemyStanding;
		std::vector<QPixmap*> m_humanPlayerMovingLeft;
		std::vector<QPixmap*> m_computerEnemyMovingLeft;
		std::vector<QPixmap*> m_humanPlayerMovingUp;
		std::vector<QPixmap*> m_computerEnemyMovingUp;
		std::vector<QPixmap*> m_humanPlayerMovingRight;
		std::vector<QPixmap*> m_computerEnemyMovingRight;
		std::vector<QPixmap*> m_humanPlayerMovingDown;
		std::vector<QPixmap*> m_computerEnemyMovingDown;
		QPixmap *m_bomb;
		QPixmap *m_wallSolid;
		QPixmap *m_wallLoose;
		QPixmap *m_powerUp;
		QPixmap *m_powerUpMaxBomb;
		QPixmap *m_powerUpMaxVelocity;
		QPixmap *m_powerUpMaxBombRange;
		QPixmap *m_explodedBombCenter;
		QPixmap *m_explodedBombFlame;
		QPixmap *m_explodedBombEnd;
	};
}

#endif
