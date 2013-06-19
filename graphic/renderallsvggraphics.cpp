#include "renderallsvggraphics.h"
#include <QtSvg/QtSvg>

using namespace Graphic;

RenderAllSvgGraphics::RenderAllSvgGraphics(const double pixelPerMeter) :
	m_pixelPerMeter(pixelPerMeter)
{
	renderPlayerItem();
	renderBombItem();
	renderExplodedBombItems();
	renderPowerUpItems();
	renderWallItems();
	renderCellBackgroundItem();
}

RenderAllSvgGraphics::~RenderAllSvgGraphics()
{
	delete m_playerRenderer;
	delete m_bombRenderer;
	delete m_explodedBombCenterRenderer;
	delete m_explodedBombFlameRenderer;
	delete m_powerUpRenderer;
	delete m_wallLooseRenderer;
	delete m_wallSolidRenderer;
	delete m_cellBackgroundRenderer;
}

void RenderAllSvgGraphics::renderPlayerItem()
{
	m_playerRenderer = new QSvgRenderer(QString("resources/graphics/player_standing.svg"));
}

void RenderAllSvgGraphics::renderBombItem()
{
	m_bombRenderer = new QSvgRenderer(QString("resources/graphics/bomb_planted.svg"));
}

void RenderAllSvgGraphics::renderExplodedBombItems()
{
	m_explodedBombCenterRenderer = new QSvgRenderer(QString("resources/graphics/explosion_center.svg"));
	m_explodedBombFlameRenderer = new QSvgRenderer(QString("resources/graphics/explosion_flame.svg"));
}

void RenderAllSvgGraphics::renderPowerUpItems()
{
	m_powerUpRenderer = new QSvgRenderer(QString("resources/graphics/powerup.svg"));
}

void RenderAllSvgGraphics::renderWallItems()
{
	m_wallSolidRenderer = new QSvgRenderer(QString("resources/graphics/wall_solid.svg"));
	m_wallLooseRenderer = new QSvgRenderer(QString("resources/graphics/wall_loose.svg"));
}

void RenderAllSvgGraphics::renderCellBackgroundItem()
{
	m_cellBackgroundRenderer = new QSvgRenderer(QString("resources/graphics/bg_cell_pattern.svg"));
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

QGraphicsSvgItem* RenderAllSvgGraphics::getNewSolidWallItem()
{
	QGraphicsSvgItem *solidWall = new QGraphicsSvgItem();
	solidWall->setSharedRenderer(m_wallSolidRenderer);
	return solidWall;
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewLooseWallItem()
{
	QGraphicsSvgItem *looseWall = new QGraphicsSvgItem();
	looseWall->setSharedRenderer(m_wallLooseRenderer);
	return looseWall;
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewPowerUpItem()
{
	QGraphicsSvgItem *powerUp = new QGraphicsSvgItem();
	powerUp->setSharedRenderer(m_powerUpRenderer);
	return powerUp;
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewCellBackgroundItem()
{
	QGraphicsSvgItem *cellBG = new QGraphicsSvgItem();
	cellBG->setSharedRenderer(m_cellBackgroundRenderer);
	return cellBG;
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewExplodedBombCenterItem()
{
	QGraphicsSvgItem *explosionCenter = new QGraphicsSvgItem();
	explosionCenter->setSharedRenderer(m_explodedBombCenterRenderer);
	return explosionCenter;
}

QGraphicsSvgItem* RenderAllSvgGraphics::getNewExplodedBombFlameItem()
{
	QGraphicsSvgItem *explosionFlame = new QGraphicsSvgItem();
	explosionFlame->setSharedRenderer(m_explodedBombFlameRenderer);
	return explosionFlame;
}
