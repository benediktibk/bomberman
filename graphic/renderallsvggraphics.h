#ifndef GRAPHIC_RENDERALLSVGGRAPHICS_H
#define GRAPHIC_RENDERALLSVGGRAPHICS_H

class QGraphicsSvgItem;

namespace Graphic
{
class RenderAllSvgGraphics
{
public:
	RenderAllSvgGraphics(const double pixelPerMeter);
	QGraphicsSvgItem* getPlayerItem();

private:
	void renderPlayerItem();

private:
	const double m_pixelPerMeter;
	QGraphicsSvgItem *m_playerItem;

};
}

#endif
