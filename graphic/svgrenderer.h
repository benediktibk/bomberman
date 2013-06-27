#ifndef GRAPHIC_SVGRENDERER_H
#define GRAPHIC_SVGRENDERER_H

#include "common/powerupstate.h"
#include <vector>

class QGraphicsItem;
class QSvgRenderer;

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

		QGraphicsItem* getNewPlayerStandingItem(unsigned int playerID);
		QGraphicsItem* getNewPlayerMovingLeftItem(unsigned int playerId);
		QGraphicsItem* getNewPlayerMovingUpItem(unsigned int playerId);
		QGraphicsItem* getNewPlayerMovingRightItem(unsigned int playerId);
		QGraphicsItem* getNewPlayerMovingDownItem(unsigned int playerId);
		QGraphicsItem* getNewBombItem();
		QGraphicsItem* getNewSolidWallItem();
		QGraphicsItem* getNewLooseWallItem();
		QGraphicsItem* getNewPowerUpItem(Common::PowerUpType powerUpType = Common::PowerUpTypeNone);
		QGraphicsItem* getNewCellBackgroundItem();
		QGraphicsItem* getNewExplodedBombCenterItem();
		QGraphicsItem* getNewExplodedBombFlameItem();
		QGraphicsItem* getNewExplodedBombEndItem();

	private:
		void renderPlayerItems();
		void renderBombItem();
		void renderWallItems();
		void renderPowerUpItems();
		void renderExplodedBombItems();
		void renderCellBackgroundItem();
		void clearRendererList(std::vector<QSvgRenderer*> &list);
		QGraphicsItem* getNewGraphicsItemFromRenderer(const std::vector<QSvgRenderer*> &list, unsigned int index) const;

	private:
		const double m_pixelPerMeter;
		const Common::GameState &m_gameState;
		std::vector<QSvgRenderer*> m_humanPlayerStanding;
		std::vector<QSvgRenderer*> m_computerEnemyStanding;
		std::vector<QSvgRenderer*> m_humanPlayerMovingLeft;
		std::vector<QSvgRenderer*> m_computerEnemyMovingLeft;
		std::vector<QSvgRenderer*> m_humanPlayerMovingUp;
		std::vector<QSvgRenderer*> m_computerEnemyMovingUp;
		std::vector<QSvgRenderer*> m_humanPlayerMovingRight;
		std::vector<QSvgRenderer*> m_computerEnemyMovingRight;
		std::vector<QSvgRenderer*> m_humanPlayerMovingDown;
		std::vector<QSvgRenderer*> m_computerEnemyMovingDown;
		QSvgRenderer *m_bombRenderer;
		QSvgRenderer *m_wallSolidRenderer;
		QSvgRenderer *m_wallLooseRenderer;
		QSvgRenderer *m_powerUpRenderer;
		QSvgRenderer *m_powerUpMaxBombRenderer;
		QSvgRenderer *m_powerUpMaxVelocityRenderer;
		QSvgRenderer *m_powerUpMaxBombRangeRenderer;
		QSvgRenderer *m_cellBackgroundRenderer;
		QSvgRenderer *m_explodedBombCenterRenderer;
		QSvgRenderer *m_explodedBombFlameRenderer;
		QSvgRenderer *m_explodedBombEndRenderer;
	};
}

#endif
