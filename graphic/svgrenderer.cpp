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
}

SvgRenderer::~SvgRenderer()
{
	clearPixmapList(m_humanPlayerStanding);
	clearPixmapList(m_computerEnemyStanding);
	clearPixmapList(m_humanPlayerMovingLeft);
	clearPixmapList(m_computerEnemyMovingLeft);
	clearPixmapList(m_humanPlayerMovingUp);
	clearPixmapList(m_computerEnemyMovingUp);
	clearPixmapList(m_humanPlayerMovingRight);
	clearPixmapList(m_computerEnemyMovingRight);
	clearPixmapList(m_humanPlayerMovingDown);
	clearPixmapList(m_computerEnemyMovingDown);

	delete m_bomb;
	delete m_explodedBombCenter;
	delete m_explodedBombFlame;
	delete m_powerUp;
	delete m_wallLoose;
	delete m_wallSolid;
	delete m_explodedBombEnd;
	delete m_powerUpMaxBombRange;
	delete m_powerUpMaxBomb;
	delete m_powerUpMaxVelocity;
}

void SvgRenderer::renderPlayerItems()
{
	m_humanPlayerStanding.push_back(createPixmapFromSvg("resources/graphics/player_standing_1.svg"));
	m_humanPlayerStanding.push_back(createPixmapFromSvg("resources/graphics/player_standing_2.svg"));
	m_computerEnemyStanding.push_back(createPixmapFromSvg("resources/graphics/player_standing_3.svg"));
	m_computerEnemyStanding.push_back(createPixmapFromSvg("resources/graphics/player_standing_4.svg"));

	m_humanPlayerMovingLeft.push_back(createPixmapFromSvg("resources/graphics/player_moving_left_1.svg"));
	m_humanPlayerMovingLeft.push_back(createPixmapFromSvg("resources/graphics/player_moving_left_2.svg"));
	m_computerEnemyMovingLeft.push_back(createPixmapFromSvg("resources/graphics/player_moving_left_3.svg"));
	m_computerEnemyMovingLeft.push_back(createPixmapFromSvg("resources/graphics/player_moving_left_4.svg"));

	m_humanPlayerMovingUp.push_back(createPixmapFromSvg("resources/graphics/player_moving_up_1.svg"));
	m_humanPlayerMovingUp.push_back(createPixmapFromSvg("resources/graphics/player_moving_up_2.svg"));
	m_computerEnemyMovingUp.push_back(createPixmapFromSvg("resources/graphics/player_moving_up_3.svg"));
	m_computerEnemyMovingUp.push_back(createPixmapFromSvg("resources/graphics/player_moving_up_4.svg"));

	m_humanPlayerMovingRight.push_back(createPixmapFromSvg("resources/graphics/player_moving_right_1.svg"));
	m_humanPlayerMovingRight.push_back(createPixmapFromSvg("resources/graphics/player_moving_right_2.svg"));
	m_computerEnemyMovingRight.push_back(createPixmapFromSvg("resources/graphics/player_moving_right_3.svg"));
	m_computerEnemyMovingRight.push_back(createPixmapFromSvg("resources/graphics/player_moving_right_4.svg"));

	m_humanPlayerMovingDown.push_back(createPixmapFromSvg("resources/graphics/player_moving_down_1.svg"));
	m_humanPlayerMovingDown.push_back(createPixmapFromSvg("resources/graphics/player_moving_down_2.svg"));
	m_computerEnemyMovingDown.push_back(createPixmapFromSvg("resources/graphics/player_moving_down_3.svg"));
	m_computerEnemyMovingDown.push_back(createPixmapFromSvg("resources/graphics/player_moving_down_4.svg"));
}

void SvgRenderer::renderBombItem()
{
	m_bomb = createPixmapFromSvg("resources/graphics/bomb_planted.svg");
}

void SvgRenderer::renderExplodedBombItems()
{
	m_explodedBombCenter = createPixmapFromSvg("resources/graphics/explosion_center.svg");
	m_explodedBombFlame = createPixmapFromSvg("resources/graphics/explosion_flame.svg");
	m_explodedBombEnd = createPixmapFromSvg("resources/graphics/explosion_end.svg");
}

void SvgRenderer::renderPowerUpItems()
{
	m_powerUp = createPixmapFromSvg("resources/graphics/powerup.svg");
	m_powerUpMaxBombRange = createPixmapFromSvg("resources/graphics/powerup_range.svg");
	m_powerUpMaxBomb = createPixmapFromSvg("resources/graphics/powerup_maxbombs.svg");
	m_powerUpMaxVelocity = createPixmapFromSvg("resources/graphics/powerup_speed.svg");
}

void SvgRenderer::renderWallItems()
{
	m_wallSolid = createPixmapFromSvg("resources/graphics/wall_solid.svg");
	m_wallLoose = createPixmapFromSvg("resources/graphics/wall_loose.svg");
}

void SvgRenderer::clearPixmapList(vector<QPixmap*> &list)
{
	for (vector<QPixmap*>::iterator i = list.begin(); i != list.end(); ++i)
		delete *i;
	list.clear();
}

QGraphicsItem *SvgRenderer::getNewGraphicsItemFromRenderer(const vector<QPixmap*> &list, unsigned int index, double /*dimension*/) const
{
	unsigned int realIndex = index % list.size();
	const QPixmap &pixmap = *(list.at(realIndex));
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
	//item->setScale(dimension*m_pixelPerMeter);
	return item;
}

QPixmap* SvgRenderer::createPixmapFromSvg(const string &file) const
{
	QSvgRenderer renderer(QString(file.c_str()));
	QImage image(m_pixelPerMeter, m_pixelPerMeter, QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	QPainter painter(&image);
	renderer.render(&painter);
	return new QPixmap(QPixmap::fromImage(image));
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

QGraphicsItem* SvgRenderer::getNewBombItem(double /*dimension*/)
{
	QGraphicsPixmapItem *bomb = new QGraphicsPixmapItem(*m_bomb);
	//bomb->setScale(m_pixelPerMeter*dimension);
	return bomb;
}

QGraphicsItem* SvgRenderer::getNewSolidWallItem(double /*dimension*/)
{
	QGraphicsPixmapItem *solidWall = new QGraphicsPixmapItem(*m_wallSolid);
	//solidWall->setScale(m_pixelPerMeter*dimension);
	return solidWall;
}

QGraphicsItem* SvgRenderer::getNewLooseWallItem(double /*dimension*/)
{
	QGraphicsPixmapItem *looseWall = new QGraphicsPixmapItem(*m_wallLoose);
	//looseWall->setScale(m_pixelPerMeter*dimension);
	return looseWall;
}

QGraphicsItem* SvgRenderer::getNewPowerUpItem(Common::PowerUpType powerUpType, double /*dimension*/)
{
	QGraphicsPixmapItem *powerUp = 0;

	switch (powerUpType)
	{
		case Common::PowerUpTypeMaxBomb:
			powerUp = new QGraphicsPixmapItem(*m_powerUpMaxBomb);
			break;
		case Common::PowerUpTypeMaxBombRange:
			powerUp = new QGraphicsPixmapItem(*m_powerUpMaxBombRange);
			break;
		case Common::PowerUpTypeMaxVelocity:
			powerUp = new QGraphicsPixmapItem(*m_powerUpMaxVelocity);
			break;
		case Common::PowerUpTypeNone:
			powerUp = new QGraphicsPixmapItem(*m_powerUp);
			break;
	}

	//powerUp->setScale(m_pixelPerMeter*dimension);
	return powerUp;
}

QGraphicsItem* SvgRenderer::getNewExplodedBombCenterItem(double /*dimension*/)
{
	QGraphicsPixmapItem *explosionCenter = new QGraphicsPixmapItem(*m_explodedBombCenter);
	//explosionCenter->setScale(m_pixelPerMeter*dimension);
	return explosionCenter;
}

QGraphicsItem* SvgRenderer::getNewExplodedBombFlameItem(double /*dimension*/)
{
	QGraphicsPixmapItem *explosionFlame = new QGraphicsPixmapItem(*m_explodedBombFlame);
	//explosionFlame->setScale(m_pixelPerMeter*dimension);
	return explosionFlame;
}

QGraphicsItem* SvgRenderer::getNewExplodedBombEndItem(double /*dimension*/)
{
	QGraphicsPixmapItem *explosionEnd = new QGraphicsPixmapItem(*m_explodedBombEnd);
	//explosionEnd->setScale(m_pixelPerMeter*dimension);
	return explosionEnd;
}
