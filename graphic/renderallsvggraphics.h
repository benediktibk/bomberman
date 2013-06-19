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
	~RenderAllSvgGraphics();

private:
	void renderPlayerItem();

private:
	const double m_pixelPerMeter;
	QSvgRenderer *m_playerRenderer;

};
}

#endif
