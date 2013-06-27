#ifndef GRAPHIC_SVGRENDERER_H
#define GRAPHIC_SVGRENDERER_H

#include "common/powerupstate.h"

class QGraphicsSvgItem;
class QSvgRenderer;

namespace Graphic
{
class SvgRenderer
{
public:
	SvgRenderer(const double pixelPerMeter);
	QGraphicsSvgItem *getNewPlayerStandingItem();
	QGraphicsSvgItem *getNewPlayerMovingLeftItem();
	QGraphicsSvgItem *getNewPlayerMovingUpItem();
	QGraphicsSvgItem *getNewPlayerMovingRightItem();
	QGraphicsSvgItem *getNewPlayerMovingDownItem();
	QGraphicsSvgItem *getNewBombItem();
	QGraphicsSvgItem *getNewSolidWallItem();
	QGraphicsSvgItem *getNewLooseWallItem();
	QGraphicsSvgItem *getNewPowerUpItem(Common::PowerUpType powerUpType = Common::PowerUpTypeNone);
	QGraphicsSvgItem *getNewCellBackgroundItem();
	QGraphicsSvgItem *getNewExplodedBombCenterItem();
	QGraphicsSvgItem *getNewExplodedBombFlameItem();
	QGraphicsSvgItem *getNewExplodedBombEndItem();
	~SvgRenderer();

private:
	void renderPlayerItems();
	void renderBombItem();
	void renderWallItems();
	void renderPowerUpItems();
	void renderExplodedBombItems();
	void renderCellBackgroundItem();

private:
	const double m_pixelPerMeter;

	QSvgRenderer *m_playerStandingRenderer_1;
	QSvgRenderer *m_playerStandingRenderer_2;
	QSvgRenderer *m_playerStandingRenderer_3;
	QSvgRenderer *m_playerStandingRenderer_4;

	QSvgRenderer *m_playerMovingLeftRenderer_1;
	QSvgRenderer *m_playerMovingLeftRenderer_2;
	QSvgRenderer *m_playerMovingLeftRenderer_3;
	QSvgRenderer *m_playerMovingLeftRenderer_4;

	QSvgRenderer *m_playerMovingUpRenderer_1;
	QSvgRenderer *m_playerMovingUpRenderer_2;
	QSvgRenderer *m_playerMovingUpRenderer_3;
	QSvgRenderer *m_playerMovingUpRenderer_4;

	QSvgRenderer *m_playerMovingRightRenderer_1;
	QSvgRenderer *m_playerMovingRightRenderer_2;
	QSvgRenderer *m_playerMovingRightRenderer_3;
	QSvgRenderer *m_playerMovingRightRenderer_4;

	QSvgRenderer *m_playerMovingDownRenderer_1;
	QSvgRenderer *m_playerMovingDownRenderer_2;
	QSvgRenderer *m_playerMovingDownRenderer_3;
	QSvgRenderer *m_playerMovingDownRenderer_4;

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
