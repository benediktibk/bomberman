#include "renderallsvggraphics.h"
#include <QtSvg/QtSvg>

using namespace Graphic;

RenderAllSvgGraphics::RenderAllSvgGraphics(const double pixelPerMeter) :
	m_pixelPerMeter(pixelPerMeter)
{
	renderPlayerItem();
	renderBombItem();
}

RenderAllSvgGraphics::~RenderAllSvgGraphics()
{
	delete m_playerRenderer;
}

void RenderAllSvgGraphics::renderPlayerItem()
{
	m_playerRenderer = new QSvgRenderer(QString("resources/graphics/player_standing.svg"));
}

void RenderAllSvgGraphics::renderBombItem()
{
	m_bombRenderer = new QSvgRenderer(QString("resources/graphics/bomb_planted.svg"));
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewPlayerItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerRenderer);
	return player;
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewBombItem()
{
	QGraphicsSvgItem *bomb = new QGraphicsSvgItem();
	bomb->setSharedRenderer(m_bombRenderer);
	return bomb;
}
