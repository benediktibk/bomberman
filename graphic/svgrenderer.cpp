#include "svgrenderer.h"
#include <QtSvg/QtSvg>

using namespace Graphic;

SvgRenderer::SvgRenderer(const double pixelPerMeter) :
	m_pixelPerMeter(pixelPerMeter)
{
	renderPlayerItems();
	renderBombItem();
	renderExplodedBombItems();
	renderPowerUpItems();
	renderWallItems();
	renderCellBackgroundItem();
}

SvgRenderer::~SvgRenderer()
{
	delete m_playerStandingRenderer;
	delete m_bombRenderer;
	delete m_explodedBombCenterRenderer;
	delete m_explodedBombFlameRenderer;
	delete m_powerUpRenderer;
	delete m_wallLooseRenderer;
	delete m_wallSolidRenderer;
	delete m_cellBackgroundRenderer;
}

void SvgRenderer::renderPlayerItems()
{
	m_playerStandingRenderer = new QSvgRenderer(QString("resources/graphics/player_standing.svg"));
	m_playerMovingLeftRenderer = new QSvgRenderer(QString("resources/graphics/player_moving_left.svg"));
	m_playerMovingUpRenderer = new QSvgRenderer(QString("resources/graphics/player_moving_up.svg"));
	m_playerMovingRightRenderer = new QSvgRenderer(QString("resources/graphics/player_moving_right.svg"));
	m_playerMovingDownRenderer = new QSvgRenderer(QString("resources/graphics/player_moving_down.svg"));
}

void SvgRenderer::renderBombItem()
{
	m_bombRenderer = new QSvgRenderer(QString("resources/graphics/bomb_planted.svg"));
}

void SvgRenderer::renderExplodedBombItems()
{
	m_explodedBombCenterRenderer = new QSvgRenderer(QString("resources/graphics/explosion_center.svg"));
	m_explodedBombFlameRenderer = new QSvgRenderer(QString("resources/graphics/explosion_flame.svg"));
}

void SvgRenderer::renderPowerUpItems()
{
	m_powerUpRenderer = new QSvgRenderer(QString("resources/graphics/powerup.svg"));
}

void SvgRenderer::renderWallItems()
{
	m_wallSolidRenderer = new QSvgRenderer(QString("resources/graphics/wall_solid.svg"));
	m_wallLooseRenderer = new QSvgRenderer(QString("resources/graphics/wall_loose.svg"));
}

void SvgRenderer::renderCellBackgroundItem()
{
	m_cellBackgroundRenderer = new QSvgRenderer(QString("resources/graphics/bg_cell_pattern.svg"));
}

QGraphicsSvgItem* SvgRenderer::getNewPlayerStandingItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerStandingRenderer);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingLeftItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingLeftRenderer);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingUpItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingUpRenderer);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingRightItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingRightRenderer);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingDownItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingDownRenderer);
	return player;
}

QGraphicsSvgItem* SvgRenderer::getNewBombItem()
{
	QGraphicsSvgItem *bomb = new QGraphicsSvgItem();
	bomb->setSharedRenderer(m_bombRenderer);
	return bomb;
}

QGraphicsSvgItem* SvgRenderer::getNewSolidWallItem()
{
	QGraphicsSvgItem *solidWall = new QGraphicsSvgItem();
	solidWall->setSharedRenderer(m_wallSolidRenderer);
	return solidWall;
}

QGraphicsSvgItem* SvgRenderer::getNewLooseWallItem()
{
	QGraphicsSvgItem *looseWall = new QGraphicsSvgItem();
	looseWall->setSharedRenderer(m_wallLooseRenderer);
	return looseWall;
}

QGraphicsSvgItem* SvgRenderer::getNewPowerUpItem()
{
	QGraphicsSvgItem *powerUp = new QGraphicsSvgItem();
	powerUp->setSharedRenderer(m_powerUpRenderer);
	return powerUp;
}

QGraphicsSvgItem* SvgRenderer::getNewCellBackgroundItem()
{
	QGraphicsSvgItem *cellBG = new QGraphicsSvgItem();
	cellBG->setSharedRenderer(m_cellBackgroundRenderer);
	return cellBG;
}

QGraphicsSvgItem* SvgRenderer::getNewExplodedBombCenterItem()
{
	QGraphicsSvgItem *explosionCenter = new QGraphicsSvgItem();
	explosionCenter->setSharedRenderer(m_explodedBombCenterRenderer);
	return explosionCenter;
}

QGraphicsSvgItem* SvgRenderer::getNewExplodedBombFlameItem()
{
	QGraphicsSvgItem *explosionFlame = new QGraphicsSvgItem();
	explosionFlame->setSharedRenderer(m_explodedBombFlameRenderer);
	return explosionFlame;
}
