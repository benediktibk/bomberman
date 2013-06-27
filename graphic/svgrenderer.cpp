#include "graphic/svgrenderer.h"
#include "common/gamestate.h"
#include <QtSvg/QtSvg>

using namespace Graphic;
using namespace std;

SvgRenderer::SvgRenderer(const double pixelPerMeter, const Common::GameState &gameState) :
	m_pixelPerMeter(pixelPerMeter),
	m_gameState(gameState)
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
	clearRendererList(m_humanPlayerStanding);
	clearRendererList(m_computerEnemyStanding);
	clearRendererList(m_humanPlayerMovingLeft);
	clearRendererList(m_computerEnemyMovingLeft);
	clearRendererList(m_humanPlayerMovingUp);
	clearRendererList(m_computerEnemyMovingUp);
	clearRendererList(m_humanPlayerMovingRight);
	clearRendererList(m_computerEnemyMovingRight);
	clearRendererList(m_humanPlayerMovingDown);
	clearRendererList(m_computerEnemyMovingDown);

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
	m_humanPlayerStanding.push_back(new QSvgRenderer(QString("resources/graphics/player_standing_1.svg")));
	m_humanPlayerStanding.push_back(new QSvgRenderer(QString("resources/graphics/player_standing_2.svg")));
	m_computerEnemyStanding.push_back(new QSvgRenderer(QString("resources/graphics/player_standing_3.svg")));
	m_computerEnemyStanding.push_back(new QSvgRenderer(QString("resources/graphics/player_standing_4.svg")));

	m_humanPlayerMovingLeft.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_left_1.svg")));
	m_humanPlayerMovingLeft.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_left_2.svg")));
	m_computerEnemyMovingLeft.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_left_3.svg")));
	m_computerEnemyMovingLeft.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_left_4.svg")));

	m_humanPlayerMovingUp.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_up_1.svg")));
	m_humanPlayerMovingUp.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_up_2.svg")));
	m_computerEnemyMovingUp.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_up_3.svg")));
	m_computerEnemyMovingUp.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_up_4.svg")));

	m_humanPlayerMovingRight.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_right_1.svg")));
	m_humanPlayerMovingRight.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_right_2.svg")));
	m_computerEnemyMovingRight.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_right_3.svg")));
	m_computerEnemyMovingRight.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_right_4.svg")));

	m_humanPlayerMovingDown.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_down_1.svg")));
	m_humanPlayerMovingDown.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_down_2.svg")));
	m_computerEnemyMovingDown.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_down_3.svg")));
	m_computerEnemyMovingDown.push_back(new QSvgRenderer(QString("resources/graphics/player_moving_down_4.svg")));
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

void SvgRenderer::clearRendererList(vector<QSvgRenderer*> &list)
{
	for (vector<QSvgRenderer*>::iterator i = list.begin(); i != list.end(); ++i)
		delete *i;
	list.clear();
}

QGraphicsItem *SvgRenderer::getNewGraphicsItemFromRenderer(const vector<QSvgRenderer*> &list, unsigned int index, double dimension) const
{
	QGraphicsSvgItem *item = new QGraphicsSvgItem();
	unsigned int realIndex = index % list.size();
	item->setSharedRenderer(list.at(realIndex));
	item->setScale(0.001*dimension*m_pixelPerMeter);
	return item;
}

QGraphicsItem* SvgRenderer::getNewPlayerStandingItem(unsigned int playerID, double dimension)
{
	if (m_gameState.isHumanPlayerID(playerID))
	{
		unsigned int index = m_gameState.getIndexOfHumanPlayer(playerID);
		return getNewGraphicsItemFromRenderer(m_humanPlayerStanding, index, dimension);
	}
	else
	{
		unsigned int index = m_gameState.getIndexOfComputerEnemy(playerID);
		return getNewGraphicsItemFromRenderer(m_computerEnemyStanding, index, dimension);
	}
}

QGraphicsItem *SvgRenderer::getNewPlayerMovingLeftItem(unsigned int playerID, double dimension)
{
	if (m_gameState.isHumanPlayerID(playerID))
	{
		unsigned int index = m_gameState.getIndexOfHumanPlayer(playerID);
		return getNewGraphicsItemFromRenderer(m_humanPlayerMovingLeft, index, dimension);
	}
	else
	{
		unsigned int index = m_gameState.getIndexOfComputerEnemy(playerID);
		return getNewGraphicsItemFromRenderer(m_computerEnemyMovingLeft, index, dimension);
	}
}

QGraphicsItem *SvgRenderer::getNewPlayerMovingUpItem(unsigned int playerID, double dimension)
{
	if (m_gameState.isHumanPlayerID(playerID))
	{
		unsigned int index = m_gameState.getIndexOfHumanPlayer(playerID);
		return getNewGraphicsItemFromRenderer(m_humanPlayerMovingUp, index, dimension);
	}
	else
	{
		unsigned int index = m_gameState.getIndexOfComputerEnemy(playerID);
		return getNewGraphicsItemFromRenderer(m_computerEnemyMovingUp, index, dimension);
	}
}

QGraphicsItem *SvgRenderer::getNewPlayerMovingRightItem(unsigned int playerID, double dimension)
{
	if (m_gameState.isHumanPlayerID(playerID))
	{
		unsigned int index = m_gameState.getIndexOfHumanPlayer(playerID);
		return getNewGraphicsItemFromRenderer(m_humanPlayerMovingRight, index, dimension);
	}
	else
	{
		unsigned int index = m_gameState.getIndexOfComputerEnemy(playerID);
		return getNewGraphicsItemFromRenderer(m_computerEnemyMovingRight, index, dimension);
	}
}

QGraphicsItem *SvgRenderer::getNewPlayerMovingDownItem(unsigned int playerID, double dimension)
{
	if (m_gameState.isHumanPlayerID(playerID))
	{
		unsigned int index = m_gameState.getIndexOfHumanPlayer(playerID);
		return getNewGraphicsItemFromRenderer(m_humanPlayerMovingDown, index, dimension);
	}
	else
	{
		unsigned int index = m_gameState.getIndexOfComputerEnemy(playerID);
		return getNewGraphicsItemFromRenderer(m_computerEnemyMovingDown, index, dimension);
	}
}

QGraphicsItem* SvgRenderer::getNewBombItem(double dimension)
{
	QGraphicsSvgItem *bomb = new QGraphicsSvgItem();
	bomb->setSharedRenderer(m_bombRenderer);
	bomb->setScale(0.001*m_pixelPerMeter*dimension);
	return bomb;
}

QGraphicsItem* SvgRenderer::getNewSolidWallItem(double dimension)
{
	QGraphicsSvgItem *solidWall = new QGraphicsSvgItem();
	solidWall->setSharedRenderer(m_wallSolidRenderer);
	solidWall->setScale(0.001*m_pixelPerMeter*dimension);
	return solidWall;
}

QGraphicsItem* SvgRenderer::getNewLooseWallItem(double dimension)
{
	QGraphicsSvgItem *looseWall = new QGraphicsSvgItem();
	looseWall->setSharedRenderer(m_wallLooseRenderer);
	looseWall->setScale(0.001*m_pixelPerMeter*dimension);
	return looseWall;
}

QGraphicsItem* SvgRenderer::getNewPowerUpItem(Common::PowerUpType powerUpType, double dimension)
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

	powerUp->setScale(0.001*m_pixelPerMeter*dimension);

	return powerUp;
}

QGraphicsItem* SvgRenderer::getNewCellBackgroundItem(double dimension)
{
	QGraphicsSvgItem *cellBG = new QGraphicsSvgItem();
	cellBG->setSharedRenderer(m_cellBackgroundRenderer);
	cellBG->setScale(0.001*m_pixelPerMeter*dimension);
	return cellBG;
}

QGraphicsItem* SvgRenderer::getNewExplodedBombCenterItem(double dimension)
{
	QGraphicsSvgItem *explosionCenter = new QGraphicsSvgItem();
	explosionCenter->setSharedRenderer(m_explodedBombCenterRenderer);
	explosionCenter->setScale(0.001*m_pixelPerMeter*dimension);
	return explosionCenter;
}

QGraphicsItem* SvgRenderer::getNewExplodedBombFlameItem(double dimension)
{
	QGraphicsSvgItem *explosionFlame = new QGraphicsSvgItem();
	explosionFlame->setSharedRenderer(m_explodedBombFlameRenderer);
	explosionFlame->setScale(0.001*m_pixelPerMeter*dimension);
	return explosionFlame;
}

QGraphicsItem* SvgRenderer::getNewExplodedBombEndItem(double dimension)
{
	QGraphicsSvgItem *explosionEnd = new QGraphicsSvgItem();
	explosionEnd->setSharedRenderer(m_explodedBombEndRenderer);
	explosionEnd->setScale(0.001*m_pixelPerMeter*dimension);
	return explosionEnd;
}
