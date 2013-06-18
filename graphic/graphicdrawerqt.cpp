#include "graphic/graphicdrawerqt.h"
#include "graphic/player.h"
#include "graphic/wall.h"
#include "graphic/bomb.h"
#include "graphic/powerup.h"
#include "graphic/explodedbomb.h"
#include "graphic/point.h"
#include "graphic/cellbackground.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>
#include <QImage>
#include <QPainter>
#include <QtSvg/QtSvg>
#include <QtOpenGL/QGLWidget>
#include <assert.h>

using namespace Graphic;
using namespace Common;
using namespace std;
using namespace Qt;

GraphicDrawerQt::GraphicDrawerQt(QGraphicsView &view, bool enableOpenGL) :
	m_view(view),
	m_scene(new QGraphicsScene()),
	m_pixelPerMeter(40),
	m_firstRedraw(true),
	m_minimumViewDistance(4),
	m_minimumViewDistanceInPixel(m_minimumViewDistance*m_pixelPerMeter),
	m_responsibilityValid(false)
{
	if (enableOpenGL)
		m_view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

	QSvgRenderer renderer(QString("resources/graphics/bg_cell_pattern.svg"));
	QImage image(m_pixelPerMeter, m_pixelPerMeter, QImage::Format_ARGB32);
	QPainter painter(&image);
	renderer.render(&painter);

	QBrush *backgroundBrush = new QBrush(image);

	m_view.setBackgroundBrush(*backgroundBrush);

	m_view.setFocusPolicy(NoFocus);
	m_view.setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
	m_view.setScene(m_scene);
}

GraphicDrawerQt::~GraphicDrawerQt()
{
	deleteWalls();
	deleteBombs();
	deletePowerUps();
	deleteBorderWalls();
	deletePlayers();
	delete m_scene;
}

void GraphicDrawerQt::setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs)
{
	assert(playerIDs.size() > 0);

	if (playerIDs.size() == 1)
	{
		m_responsibleForOnePlayer = true;
		m_playerIDResponsibleFor = playerIDs.front();
	}
	else
		m_responsibleForOnePlayer = false;

	m_responsibilityValid = true;
}

void GraphicDrawerQt::draw(const GameState &gameState)
{
	assert(m_responsibilityValid);

	if (m_firstRedraw)
	{
		drawBorderWalls(gameState.getWidth(), gameState.getHeight());
		drawCellBackgrounds(gameState.getWidth(), gameState.getHeight());
		updateViewArea(gameState);
	}

	if (m_responsibleForOnePlayer)
	{
		const PlayerState &player = gameState.getPlayerStateById(m_playerIDResponsibleFor);
		updateViewPositionForPlayer(player);
	}
	else
		m_view.fitInView(m_scene->sceneRect());

	drawWalls(gameState.getAllChangedWalls());
	drawBombs(gameState.getAllChangedBombs());
	drawPowerUps(gameState.getAllChangedPowerUps());
	drawExplodedBombs(gameState.getAllChangedExplodedBombs());
	drawPlayers(gameState);
	m_firstRedraw = false;
}

QGraphicsScene &GraphicDrawerQt::getScene()
{
	return *m_scene;
}

void GraphicDrawerQt::drawPlayers(const GameState &gameState)
{
	vector<const PlayerState*> players = gameState.getAllPlayers();

	for (vector<const PlayerState*>::const_iterator i = players.begin(); i != players.end(); ++i)
		drawPlayer(*i);
}

void GraphicDrawerQt::drawPlayer(const PlayerState *playerState)
{
	map<const PlayerState*, Player*>::iterator playerPosition = m_players.find(playerState);
	bool playerFound = playerPosition != m_players.end();
	Player* player = 0;

	if (!playerFound)
		player = new Player(*m_scene);
	else
		player = playerPosition->second;

	player->update(*playerState, m_pixelPerMeter);

	if (!playerFound)
		m_players.insert(pair<const PlayerState*, Player*>(playerState, player));
}

void GraphicDrawerQt::drawWalls(const vector<const WallState*> &walls)
{
	for (vector<const WallState*>::const_iterator i = walls.begin(); i != walls.end(); ++i)
		drawWall(*i);
}

void GraphicDrawerQt::drawWall(const WallState *wallState)
{
	if (wallState->isDestroyed())
		deleteWall(wallState);
	else
	{
		map<const WallState*, Wall*>::iterator wallPosition = m_walls.find(wallState);
		bool wallFound = wallPosition != m_walls.end();
		Wall* wall = 0;

		if (!wallFound)
			wall = new Wall(*m_scene, *wallState);
		else
			wall = wallPosition->second;

		wall->update(*wallState, m_pixelPerMeter);

		if (!wallFound)
			m_walls.insert(pair<const WallState*, Wall*>(wallState, wall));
	}
}

void GraphicDrawerQt::drawBombs(const vector<const BombState*> &bombs)
{
	for (vector<const BombState*>::const_iterator i = bombs.begin(); i != bombs.end(); ++i)
		drawBomb(*i);
}

void GraphicDrawerQt::drawBomb(const BombState *bombState)
{
	if (bombState->isDestroyed())
		deleteBomb(bombState);
	else
	{
		map<const BombState*, Bomb*>::iterator bombPosition = m_bombs.find(bombState);
		bool bombFound = bombPosition != m_bombs.end();
		Bomb* bomb = 0;

		if (!bombFound)
			bomb = new Bomb(*m_scene);
		else
			bomb = bombPosition->second;

		bomb->update(*bombState, m_pixelPerMeter);

		if (!bombFound)
			m_bombs.insert(pair<const BombState*, Bomb*>(bombState, bomb));
	}
}

void GraphicDrawerQt::drawPowerUps(const vector<const PowerUpState*> &powerUps)
{
	for (vector<const PowerUpState*>::const_iterator i = powerUps.begin(); i != powerUps.end(); ++i)
		drawPowerUp(*i);
}

void GraphicDrawerQt::drawPowerUp(const PowerUpState *powerUpState)
{
	if (powerUpState->isDestroyed())
		deletePowerUp(powerUpState);
	else
	{
		map<const PowerUpState*, PowerUp*>::iterator powerUpPosition = m_powerUps.find(powerUpState);
		bool powerUpFound = powerUpPosition != m_powerUps.end();
		PowerUp* powerUp = 0;

		if (!powerUpFound)
			powerUp = new PowerUp(*m_scene);
		else
			powerUp = powerUpPosition->second;

		powerUp->update(*powerUpState, m_pixelPerMeter);

		if (!powerUpFound)
			m_powerUps.insert(pair<const PowerUpState*, PowerUp*>(powerUpState, powerUp));
	}
}

void GraphicDrawerQt::drawExplodedBombs(const vector<const ExplodedBombState*> &explodedBombs)
{
	for (vector<const ExplodedBombState*>::const_iterator i = explodedBombs.begin(); i != explodedBombs.end(); ++i)
		drawExplodedBomb(*i);
}

void GraphicDrawerQt::drawExplodedBomb(const ExplodedBombState *explodedBombState)
{
	if (explodedBombState->isDestroyed())
		deleteExplodedBomb(explodedBombState);
	else
	{
		map<const ExplodedBombState*, ExplodedBomb*>::iterator explodedBombPosition = m_explodedBombs.find(explodedBombState);
		bool explodedBombFound = explodedBombPosition != m_explodedBombs.end();

		if (!explodedBombFound)
		{
			ExplodedBomb *explodedBomb = new ExplodedBomb(*m_scene, *explodedBombState, m_pixelPerMeter);
			m_explodedBombs.insert(pair<const ExplodedBombState*, ExplodedBomb*>(explodedBombState, explodedBomb));
		}
	}
}

void GraphicDrawerQt::updateViewArea(const GameState &gameState)
{
	unsigned int width = gameState.getWidth();
	unsigned int widthWithBorders = width + 2;
	unsigned int height = gameState.getHeight();
	unsigned int heightWithBorders = height + 2;
	unsigned int widthWithBordersInPixel = widthWithBorders*m_pixelPerMeter;
	unsigned int heightInPixel = height*m_pixelPerMeter;
	unsigned int heightWithBordersInPixel = heightWithBorders*m_pixelPerMeter;
	qreal x = (-1)*m_pixelPerMeter;
	qreal y = (-1)*static_cast<double>(heightInPixel);

	m_view.setSceneRect(x, y, widthWithBordersInPixel, heightWithBordersInPixel);
}

void GraphicDrawerQt::updateViewPositionForPlayer(const PlayerState &player)
{
	QRect maximumPlayerMovement;
	unsigned int viewWidth = m_view.width();
	unsigned int viewHeight = m_view.height();

	if (viewWidth <= m_minimumViewDistanceInPixel*2)
	{
		maximumPlayerMovement.setX(viewWidth/2);
		maximumPlayerMovement.setWidth(0);
	}
	else
	{
		maximumPlayerMovement.setX(m_minimumViewDistanceInPixel);
		maximumPlayerMovement.setWidth(viewWidth - 2*m_minimumViewDistanceInPixel);
	}

	if (viewHeight <= m_minimumViewDistanceInPixel*2)
	{
		maximumPlayerMovement.setY(viewHeight/2);
		maximumPlayerMovement.setHeight(0);
	}
	else
	{
		maximumPlayerMovement.setY(m_minimumViewDistanceInPixel);
		maximumPlayerMovement.setHeight(viewHeight - 2*m_minimumViewDistanceInPixel);
	}

	if (maximumPlayerMovement.width() == 0 && maximumPlayerMovement.height() == 0)
	{
		setViewPositionToTheCenterOfPlayer(player);
		return;
	}

	QPolygonF maximumPlayerMovementInScenePolygon = m_view.mapToScene(maximumPlayerMovement);
	QRectF maximumPlayerMovementInScene = maximumPlayerMovementInScenePolygon.boundingRect();
	Point playerPosition(player.getPosition()*m_pixelPerMeter);
	playerPosition.setX(playerPosition.getX() + player.getWidth()/2*m_pixelPerMeter);
	playerPosition.setY(playerPosition.getY() - player.getHeight()/2*m_pixelPerMeter);
	playerPosition.switchIntoQtCoordinates();
	QPointF centerOfView(maximumPlayerMovementInScene.center());
	QPointF positionToCenterOn(centerOfView);

	if (playerPosition.getY() < maximumPlayerMovementInScene.top())
	{
		double difference = maximumPlayerMovementInScene.top() - playerPosition.getY();
		positionToCenterOn.setY(centerOfView.y() - difference);
	}
	else if (playerPosition.getY() > maximumPlayerMovementInScene.bottom())
	{
		double difference = playerPosition.getY() - maximumPlayerMovementInScene.bottom();
		positionToCenterOn.setY(centerOfView.y() + difference);
	}

	if (playerPosition.getX() < maximumPlayerMovementInScene.left())
	{
		double difference = maximumPlayerMovementInScene.left() - playerPosition.getX();
		positionToCenterOn.setX(centerOfView.x() - difference);
	}
	else if (playerPosition.getX() > maximumPlayerMovementInScene.right())
	{
		double difference = playerPosition.getX() - maximumPlayerMovementInScene.right();
		positionToCenterOn.setX(centerOfView.x() + difference);
	}

	positionToCenterOn.setX(positionToCenterOn.x() - 2);
	positionToCenterOn.setY(positionToCenterOn.y() - 2);
	m_view.centerOn(positionToCenterOn);
}

void GraphicDrawerQt::setViewPositionToTheCenterOfPlayer(const PlayerState &player)
{
	Common::Point playerPosition = player.getCenterPosition();
	Graphic::Point qtPoint = playerPosition*m_pixelPerMeter;
	qtPoint.switchIntoQtCoordinates();
	m_view.centerOn(qtPoint.toQPoint());
}

void GraphicDrawerQt::drawBorderWalls(unsigned int width, unsigned int height)
{
	drawLeftBorderWalls(height);
	drawRightBorderWalls(width, height);
	drawLowerBorderWalls(width);
	drawUpperBorderWalls(width, height);
	drawEdgeBorderWalls(width, height);
}

void GraphicDrawerQt::drawLeftBorderWalls(unsigned int height)
{
	for (unsigned int y = 0; y < height; ++y)
		m_borderWalls.push_back(new Wall(*m_scene, Point(-1, y), m_pixelPerMeter));
}

void GraphicDrawerQt::drawRightBorderWalls(unsigned int width, unsigned int height)
{
	for (unsigned int y = 0; y < height; ++y)
		m_borderWalls.push_back(new Wall(*m_scene, Point(width, y), m_pixelPerMeter));
}

void GraphicDrawerQt::drawUpperBorderWalls(unsigned int width, unsigned int height)
{
	for (unsigned int x = 0; x < width; ++x)
		m_borderWalls.push_back(new Wall(*m_scene, Point(x, height), m_pixelPerMeter));
}

void GraphicDrawerQt::drawLowerBorderWalls(unsigned int width)
{
	for (unsigned int x = 0; x < width; ++x)
		m_borderWalls.push_back(new Wall(*m_scene, Point(x, -1), m_pixelPerMeter));
}

void GraphicDrawerQt::drawEdgeBorderWalls(unsigned int width, unsigned int height)
{
	m_borderWalls.push_back(new Wall(*m_scene, Point(-1, -1), m_pixelPerMeter));
	m_borderWalls.push_back(new Wall(*m_scene, Point(-1, height), m_pixelPerMeter));
	m_borderWalls.push_back(new Wall(*m_scene, Point(width, -1), m_pixelPerMeter));
	m_borderWalls.push_back(new Wall(*m_scene, Point(width, height), m_pixelPerMeter));
}

void GraphicDrawerQt::drawCellBackgrounds(unsigned int width, unsigned int height)
{
	for (unsigned int x = 0; x < width; ++x)
	{
		for (unsigned int y = 0; y < height; ++y)
		{
			m_cellBackgrounds.push_back(new CellBackground(*m_scene, Point(x, y), m_pixelPerMeter));
		}
	}
}

void GraphicDrawerQt::deleteWalls()
{
	for (map<const WallState*, Wall*>::iterator i = m_walls.begin(); i != m_walls.end(); ++i)
		delete i->second;

	m_walls.clear();
}

void GraphicDrawerQt::deleteBombs()
{
	for (map<const BombState*, Bomb*>::iterator i = m_bombs.begin(); i != m_bombs.end(); ++i)
		delete i->second;

	m_bombs.clear();
}

void GraphicDrawerQt::deletePowerUps()
{
	for (map<const PowerUpState*, PowerUp*>::iterator i = m_powerUps.begin(); i != m_powerUps.end(); ++i)
		delete i->second;

	m_powerUps.clear();;
}

void GraphicDrawerQt::deleteExplodedBombs()
{
	for (map<const ExplodedBombState*, ExplodedBomb*>::iterator i = m_explodedBombs.begin(); i != m_explodedBombs.end(); ++i)
		delete i->second;

	m_explodedBombs.clear();;
}

void GraphicDrawerQt::deleteWall(const WallState *wall)
{
	map<const WallState*, Wall*>::iterator position = m_walls.find(wall);
	delete position->second;
	m_walls.erase(position);
}

void GraphicDrawerQt::deleteBomb(const BombState *bomb)
{
	map<const BombState*, Bomb*>::iterator position = m_bombs.find(bomb);
	delete position->second;
	m_bombs.erase(position);
}

void GraphicDrawerQt::deletePowerUp(const PowerUpState *powerUp)
{
	map<const PowerUpState*, PowerUp*>::iterator position = m_powerUps.find(powerUp);
	delete position->second;
	m_powerUps.erase(position);
}

void GraphicDrawerQt::deleteExplodedBomb(const ExplodedBombState *explodedBomb)
{
	map<const ExplodedBombState*, ExplodedBomb*>::iterator position = m_explodedBombs.find(explodedBomb);
	delete position->second;
	m_explodedBombs.erase(position);
}

void GraphicDrawerQt::deleteBorderWalls()
{
	for (vector<Wall*>::iterator i = m_borderWalls.begin(); i != m_borderWalls.end(); ++i)
		delete *i;

	m_borderWalls.clear();
}

void GraphicDrawerQt::deletePlayers()
{
	for (map<const PlayerState*, Player*>::iterator i = m_players.begin(); i != m_players.end(); ++i)
		delete i->second;

	m_players.clear();
}
