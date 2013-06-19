#include "renderallsvggraphics.h"
#include <QtSvg/QtSvg>

using namespace Graphic;

RenderAllSvgGraphics::RenderAllSvgGraphics(const double pixelPerMeter) :
	m_pixelPerMeter(pixelPerMeter)
{ }

QGraphicsSvgItem* RenderAllSvgGraphics::getPlayerItem()
{
	return m_playerItem;
}

void RenderAllSvgGraphics::renderPlayerItem()
{
	m_playerItem = new QGraphicsSvgItem(QString("resources/graphics/player_standing.svg"));
	m_playerItem->setZValue(2);
}
