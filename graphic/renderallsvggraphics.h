#ifndef GRAPHIC_RENDERALLSVGGRAPHICS_H
#define GRAPHIC_RENDERALLSVGGRAPHICS_H

class QGraphicsSvgItem;
class QSvgRenderer;

namespace Graphic
{
class RenderAllSvgGraphics
{
public:
	RenderAllSvgGraphics(const double pixelPerMeter);
	QGraphicsSvgItem *getNewPlayerItem();
	QGraphicsSvgItem *getNewBombItem();
	~RenderAllSvgGraphics();

private:
	void renderPlayerItem();
	void renderBombItem();
	void renderWallItems();
	void renderPowerUpItems();
	void renderExplodedBombItems();
	void renderCellBackgroundItem();

private:
	const double m_pixelPerMeter;
	QSvgRenderer *m_playerRenderer;
	QSvgRenderer *m_bombRenderer;
	QSvgRenderer *m_wallSolidRenderer;
	QSvgRenderer *m_wallLooseRenderer;
	QSvgRenderer *m_powerUpRenderer;
	QSvgRenderer *m_cellBackgroundRenderer;
	QSvgRenderer *m_explodedBombCenterRenderer;
	QSvgRenderer *m_explodedBombFlameRenderer;

};
}

#endif
