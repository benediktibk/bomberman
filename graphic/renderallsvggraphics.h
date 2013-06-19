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

private:
	const double m_pixelPerMeter;
	QSvgRenderer *m_playerRenderer;
	QSvgRenderer *m_bombRenderer;

};
}

#endif
