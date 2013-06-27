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
	delete m_playerStandingRenderer_1;
	delete m_playerStandingRenderer_2;
	delete m_playerStandingRenderer_3;
	delete m_playerStandingRenderer_4;

	delete m_playerMovingLeftRenderer_1;
	delete m_playerMovingLeftRenderer_2;
	delete m_playerMovingLeftRenderer_3;
	delete m_playerMovingLeftRenderer_4;

	delete m_playerMovingUpRenderer_1;
	delete m_playerMovingUpRenderer_2;
	delete m_playerMovingUpRenderer_3;
	delete m_playerMovingUpRenderer_4;

	delete m_playerMovingRightRenderer_1;
	delete m_playerMovingRightRenderer_2;
	delete m_playerMovingRightRenderer_3;
	delete m_playerMovingRightRenderer_4;

	delete m_playerMovingDownRenderer_1;
	delete m_playerMovingDownRenderer_2;
	delete m_playerMovingDownRenderer_3;
	delete m_playerMovingDownRenderer_4;

	delete m_bombRenderer;
	delete m_explodedBombCenterRenderer;
	delete m_explodedBombFlameRenderer;
	delete m_powerUpRenderer;
	delete m_wallLooseRenderer;
	delete m_wallSolidRenderer;
	delete m_cellBackgroundRenderer;
	delete m_explodedBombEndRenderer;
	delete m_powerUpMaxBombRangeRenderer;
	delete m_powerUpMaxBombRenderer;
	delete m_powerUpMaxVelocityRenderer;
}

void SvgRenderer::renderPlayerItems()
{
	m_playerStandingRenderer_1 = new QSvgRenderer(QString("resources/graphics/player_standing.svg"));
	m_playerStandingRenderer_2 = new QSvgRenderer(QString("resources/graphics/player_standing_2.svg"));
	m_playerStandingRenderer_3 = new QSvgRenderer(QString("resources/graphics/player_standing_3.svg"));
	m_playerStandingRenderer_4 = new QSvgRenderer(QString("resources/graphics/player_standing_4.svg"));

	m_playerMovingLeftRenderer_1 = new QSvgRenderer(QString("resources/graphics/player_moving_left.svg"));
	m_playerMovingLeftRenderer_2 = new QSvgRenderer(QString("resources/graphics/player_moving_left_2.svg"));
	m_playerMovingLeftRenderer_3 = new QSvgRenderer(QString("resources/graphics/player_moving_left_3.svg"));
	m_playerMovingLeftRenderer_4 = new QSvgRenderer(QString("resources/graphics/player_moving_left_4.svg"));

	m_playerMovingUpRenderer_1 = new QSvgRenderer(QString("resources/graphics/player_moving_up.svg"));
	m_playerMovingUpRenderer_2 = new QSvgRenderer(QString("resources/graphics/player_moving_up_2.svg"));
	m_playerMovingUpRenderer_3 = new QSvgRenderer(QString("resources/graphics/player_moving_up_3.svg"));
	m_playerMovingUpRenderer_4 = new QSvgRenderer(QString("resources/graphics/player_moving_up_4.svg"));

	m_playerMovingRightRenderer_1 = new QSvgRenderer(QString("resources/graphics/player_moving_right.svg"));
	m_playerMovingRightRenderer_2 = new QSvgRenderer(QString("resources/graphics/player_moving_right_2.svg"));
	m_playerMovingRightRenderer_3 = new QSvgRenderer(QString("resources/graphics/player_moving_right_3.svg"));
	m_playerMovingRightRenderer_4 = new QSvgRenderer(QString("resources/graphics/player_moving_right_4.svg"));

	m_playerMovingDownRenderer_1 = new QSvgRenderer(QString("resources/graphics/player_moving_down.svg"));
	m_playerMovingDownRenderer_2 = new QSvgRenderer(QString("resources/graphics/player_moving_down_2.svg"));
	m_playerMovingDownRenderer_3 = new QSvgRenderer(QString("resources/graphics/player_moving_down_3.svg"));
	m_playerMovingDownRenderer_4 = new QSvgRenderer(QString("resources/graphics/player_moving_down_4.svg"));
}

void SvgRenderer::renderBombItem()
{
	m_bombRenderer = new QSvgRenderer(QString("resources/graphics/bomb_planted.svg"));
}

void SvgRenderer::renderExplodedBombItems()
{
	m_explodedBombCenterRenderer = new QSvgRenderer(QString("resources/graphics/explosion_center.svg"));
	m_explodedBombFlameRenderer = new QSvgRenderer(QString("resources/graphics/explosion_flame.svg"));
	m_explodedBombEndRenderer = new QSvgRenderer(QString("resources/graphics/explosion_end.svg"));
}

void SvgRenderer::renderPowerUpItems()
{
	m_powerUpRenderer = new QSvgRenderer(QString("resources/graphics/powerup.svg"));
	m_powerUpMaxBombRangeRenderer = new QSvgRenderer(QString("resources/graphics/powerup_range.svg"));
	m_powerUpMaxBombRenderer = new QSvgRenderer(QString("resources/graphics/powerup_maxbombs.svg"));
	m_powerUpMaxVelocityRenderer = new QSvgRenderer(QString("resources/graphics/powerup_speed.svg"));
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
	player->setSharedRenderer(m_playerStandingRenderer_1);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingLeftItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingLeftRenderer_1);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingUpItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingUpRenderer_1);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingRightItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingRightRenderer_1);
	return player;
}

QGraphicsSvgItem *SvgRenderer::getNewPlayerMovingDownItem()
{
	QGraphicsSvgItem *player = new QGraphicsSvgItem();
	player->setSharedRenderer(m_playerMovingDownRenderer_1);
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

QGraphicsSvgItem* SvgRenderer::getNewPowerUpItem(Common::PowerUpType powerUpType)
{
	QGraphicsSvgItem *powerUp = new QGraphicsSvgItem();

	switch (powerUpType)
	{
		case Common::PowerUpTypeMaxBomb:
			powerUp->setSharedRenderer(m_powerUpMaxBombRenderer);
			break;

		case Common::PowerUpTypeMaxBombRange:
			powerUp->setSharedRenderer(m_powerUpMaxBombRangeRenderer);
			break;

		case Common::PowerUpTypeMaxVelocity:
			powerUp->setSharedRenderer(m_powerUpMaxVelocityRenderer);
			break;

		default:
			powerUp->setSharedRenderer(m_powerUpRenderer);
			break;
	}

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

QGraphicsSvgItem* SvgRenderer::getNewExplodedBombEndItem()
{
	QGraphicsSvgItem *explosionEnd = new QGraphicsSvgItem();
	explosionEnd->setSharedRenderer(m_explodedBombEndRenderer);
	return explosionEnd;
}
