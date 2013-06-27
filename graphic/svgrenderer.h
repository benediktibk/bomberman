#ifndef GRAPHIC_SVGRENDERER_H
#define GRAPHIC_SVGRENDERER_H

#include "common/powerupstate.h"
#include <vector>

class QGraphicsSvgItem;
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

		QGraphicsSvgItem* getNewPlayerStandingItem(unsigned int playerID);
		QGraphicsSvgItem* getNewPlayerMovingLeftItem(unsigned int playerId);
		QGraphicsSvgItem* getNewPlayerMovingUpItem(unsigned int playerId);
		QGraphicsSvgItem* getNewPlayerMovingRightItem(unsigned int playerId);
		QGraphicsSvgItem* getNewPlayerMovingDownItem(unsigned int playerId);
		QGraphicsSvgItem* getNewBombItem();
		QGraphicsSvgItem* getNewSolidWallItem();
		QGraphicsSvgItem* getNewLooseWallItem();
		QGraphicsSvgItem* getNewPowerUpItem(Common::PowerUpType powerUpType = Common::PowerUpTypeNone);
		QGraphicsSvgItem* getNewCellBackgroundItem();
		QGraphicsSvgItem* getNewExplodedBombCenterItem();
		QGraphicsSvgItem* getNewExplodedBombFlameItem();
		QGraphicsSvgItem* getNewExplodedBombEndItem();

	private:
		void renderPlayerItems();
		void renderBombItem();
		void renderWallItems();
		void renderPowerUpItems();
		void renderExplodedBombItems();
		void renderCellBackgroundItem();
		void clearRendererList(std::vector<QSvgRenderer*> &list);
		QGraphicsSvgItem* getNewGraphicsItemFromRenderer(const std::vector<QSvgRenderer*> &list, unsigned int index) const;

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
