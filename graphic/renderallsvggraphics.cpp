#include "renderallsvggraphics.h"
#include <QtSvg/QtSvg>

using namespace Graphic;

RenderAllSvgGraphics::RenderAllSvgGraphics(const double pixelPerMeter) :
	m_pixelPerMeter(pixelPerMeter)
{ }

RenderAllSvgGraphics::~RenderAllSvgGraphics()
{
	delete m_playerRenderer;
}

QGraphicsSvgItem *RenderAllSvgGraphics::getNewPlayerItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerRenderer);
	return player;
}

void RenderAllSvgGraphics::renderPlayerItem()
{
	m_playerRenderer = new QSvgRenderer(QString("resources/graphics/player_standing.svg"));
}
