#ifndef GRAPHIC_SVGRENDERER_H
#define GRAPHIC_SVGRENDERER_H

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
	QGraphicsSvgItem *getNewPowerUpItem();
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
	QSvgRenderer *m_playerStandingRenderer;
	QSvgRenderer *m_playerMovingLeftRenderer;
	QSvgRenderer *m_playerMovingUpRenderer;
	QSvgRenderer *m_playerMovingRightRenderer;
	QSvgRenderer *m_playerMovingDownRenderer;
	QSvgRenderer *m_bombRenderer;
	QSvgRenderer *m_wallSolidRenderer;
	QSvgRenderer *m_wallLooseRenderer;
	QSvgRenderer *m_powerUpRenderer;
	QSvgRenderer *m_cellBackgroundRenderer;
	QSvgRenderer *m_explodedBombCenterRenderer;
	QSvgRenderer *m_explodedBombFlameRenderer;
	QSvgRenderer *m_explodedBombEndRenderer;

};
}

#endif
