#include "graphic/graphicdrawerqt.h"
#include "graphic/player.h"
#include "graphic/wall.h"
#include "graphic/bomb.h"
#include "graphic/powerup.h"
#include "graphic/explodedbomb.h"
#include "graphic/point.h"
#include "graphic/svgrenderer.h"
#include "common/stopwatch.h"
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

GraphicDrawerQt::GraphicDrawerQt(const vector<QGraphicsView*> &views, bool enableOpenGL) :
	m_views(views),
	m_scene(new QGraphicsScene()),
	m_pixelPerMeter(40),
	m_firstRedraw(true),
	m_minimumViewDistance(4),
	m_minimumViewDistanceInPixel(m_minimumViewDistance*m_pixelPerMeter),
	m_responsibilityValid(false),
	m_svgRenderer(0),
	m_backgroundBrush(0),
	m_scaleCompare(0.01),
	m_viewAreaCompare(2)
{
	createBackgroundBrush();
	configureViews(enableOpenGL);
	initializeScales();
}

GraphicDrawerQt::~GraphicDrawerQt()
{
	setScaleOfAllViewsToOne();
	deleteWalls();
	deleteBombs();
	deletePowerUps();
	deleteBorderWalls();
	deletePlayers();
	delete m_scene;
	delete m_svgRenderer;
	delete m_backgroundBrush;
}

void GraphicDrawerQt::setResponsibleForPlayers(const vector<unsigned int> &playerIDs)
{
	assert(playerIDs.size() > 0);
	assert(playerIDs.size() == m_views.size());

	m_playerIDToViewMap.clear();
	for (unsigned int i = 0; i < playerIDs.size(); ++i)
		m_playerIDToViewMap.insert(pair<unsigned int, QGraphicsView*>(playerIDs[i], m_views[i]));

	m_responsibilityValid = true;
}

double GraphicDrawerQt::draw(const GameState &gameState)
{
	StopWatch stopWatch;
	assert(m_responsibilityValid);

	if (m_firstRedraw)
	{
		assert(m_svgRenderer == 0);
		m_svgRenderer = new SvgRenderer(m_pixelPerMeter, gameState);
		drawBorderWalls(gameState.getWidth(), gameState.getHeight());
		m_sceneRect = calculateSceneRect(gameState);
		setSceneRectForViews();
		centerViewsOnPlayer(gameState);
	}

	updateViewAreas(gameState);
	drawWalls(gameState.getAllChangedWalls());
	drawBombs(gameState.getAllChangedBombs());
	drawPowerUps(gameState.getAllChangedPowerUps());
	drawExplodedBombs(gameState.getAllChangedExplodedBombs());
	drawPlayers(gameState);
	m_firstRedraw = false;

	return stopWatch.getTimeAndRestart();
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

	if (playerState->isDestroyed())
	{
		if (playerFound)
		{
			delete playerPosition->second;
			m_players.erase(playerPosition);
		}

		return;
	}

	if (!playerFound)
		player = new Player(*m_scene, *m_svgRenderer, *playerState);
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
			wall = new Wall(*m_scene, *m_svgRenderer, *wallState);
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
			bomb = new Bomb(*m_scene, *m_svgRenderer, *bombState);
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
		{
			powerUp = new PowerUp(*m_scene, *m_svgRenderer,*powerUpState, m_pixelPerMeter);
		}
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
			ExplodedBomb *explodedBomb = new ExplodedBomb(*m_scene, *m_svgRenderer, *explodedBombState, m_pixelPerMeter);
			m_explodedBombs.insert(pair<const ExplodedBombState*, ExplodedBomb*>(explodedBombState, explodedBomb));
		}
	}
}

void GraphicDrawerQt::setSceneRectForViews()
{
	for (vector<QGraphicsView*>::iterator i = m_views.begin(); i != m_views.end(); ++i)
		(*i)->setSceneRect(m_sceneRect);
}

void GraphicDrawerQt::fitWholeAreaInView(QGraphicsView &view)
{
	double currentScale = m_currentScales.at(&view);
	double scaleX = view.width()/m_sceneRect.width();
	double scaleY = view.height()/m_sceneRect.height();
	double scaleMax = min(scaleX, scaleY);

	if (!m_scaleCompare.isFuzzyEqual(scaleMax, currentScale))
		scale(scaleMax, view);
}

void GraphicDrawerQt::updateViewPositionForPlayer(const PlayerState &player, QGraphicsView &view)
{
	QRect maximumPlayerMovement;
	unsigned int viewWidth = view.width();
	unsigned int viewHeight = view.height();

	if (viewWidth <= m_minimumViewDistanceInPixel*2)
	{
		maximumPlayerMovement.setX(viewWidth/2);
		maximumPlayerMovement.setWidth(0);
	}
	else
	{
		maximumPlayerMovement.setX(m_minimumViewDistanceInPixel);
		maximumPlayerMovement.setWidth(max(0.0, viewWidth - 2*m_minimumViewDistanceInPixel));
	}

	if (viewHeight <= m_minimumViewDistanceInPixel*2)
	{
		maximumPlayerMovement.setY(viewHeight/2);
		maximumPlayerMovement.setHeight(0);
	}
	else
	{
		maximumPlayerMovement.setY(m_minimumViewDistanceInPixel);
		maximumPlayerMovement.setHeight(max(0.0, viewHeight - 2*m_minimumViewDistanceInPixel));
	}

	if (maximumPlayerMovement.width() == 0 && maximumPlayerMovement.height() == 0)
	{
		setViewPositionToTheCenterOfPlayer(player);
		return;
	}

	QPolygonF maximumPlayerMovementInScenePolygon = view.mapToScene(maximumPlayerMovement);
	QRectF maximumPlayerMovementInScene = maximumPlayerMovementInScenePolygon.boundingRect();
	Point playerPosition(player.getPosition()*m_pixelPerMeter);
	playerPosition.setX(playerPosition.getX() + player.getDimension()/2*m_pixelPerMeter);
	playerPosition.setY(playerPosition.getY() - player.getDimension()/2*m_pixelPerMeter);
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

	if (	!m_viewAreaCompare.isFuzzyEqual(centerOfView.x(), positionToCenterOn.x()) ||
			!m_viewAreaCompare.isFuzzyEqual(centerOfView.y(), positionToCenterOn.y()))
	{
		/*
		 * I don't know where these offsets come from, but with these magic
		 * values everything is fine. In Qt4 they were both 2, somehow for Qt5 I
		 * had to change them to 1. If they are not correct you can see a very strange
		 * and smooth delay in the update of the view area.
		 */
		positionToCenterOn.setX(positionToCenterOn.x() - 1);
		positionToCenterOn.setY(positionToCenterOn.y() - 1);
		view.centerOn(positionToCenterOn);
	}
}

void GraphicDrawerQt::setViewPositionToTheCenterOfPlayer(const PlayerState &player)
{
	Common::Point playerPosition = player.getCenterPosition();
	Graphic::Point qtPoint = playerPosition*m_pixelPerMeter;
	qtPoint.switchIntoQtCoordinates();
	QGraphicsView &view = *(m_playerIDToViewMap.at(player.getId()));
	view.centerOn(qtPoint.toQPoint());
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
		m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(-1, y), m_pixelPerMeter, 1));
}

void GraphicDrawerQt::drawRightBorderWalls(unsigned int width, unsigned int height)
{
	for (unsigned int y = 0; y < height; ++y)
		m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(width, y), m_pixelPerMeter, 1));
}

void GraphicDrawerQt::drawUpperBorderWalls(unsigned int width, unsigned int height)
{
	for (unsigned int x = 0; x < width; ++x)
		m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(x, height), m_pixelPerMeter, 1));
}

void GraphicDrawerQt::drawLowerBorderWalls(unsigned int width)
{
	for (unsigned int x = 0; x < width; ++x)
		m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(x, -1), m_pixelPerMeter, 1));
}

void GraphicDrawerQt::drawEdgeBorderWalls(unsigned int width, unsigned int height)
{
	m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(-1, -1), m_pixelPerMeter, 1));
	m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(-1, height), m_pixelPerMeter, 1));
	m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(width, -1), m_pixelPerMeter, 1));
	m_borderWalls.push_back(new Wall(*m_scene, *m_svgRenderer, Point(width, height), m_pixelPerMeter, 1));
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
	if (position != m_powerUps.end())
	{
		delete position->second;
		m_powerUps.erase(position);
	}
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

QRectF GraphicDrawerQt::calculateSceneRect(const GameState &gameState)
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
	return QRectF(x, y, widthWithBordersInPixel, heightWithBordersInPixel);
}

void GraphicDrawerQt::scale(double factor, QGraphicsView &view)
{
	double currentScale = m_currentScales.at(&view);
	double scaleBy = factor/currentScale;
	view.scale(scaleBy, scaleBy);
	m_currentScales.at(&view) = factor;
}

void GraphicDrawerQt::setScaleOfAllViewsToOne()
{
	for (vector<QGraphicsView*>::iterator i = m_views.begin(); i != m_views.end(); ++i)
		scale(1, **i);
}

void GraphicDrawerQt::configureView(QGraphicsView &view, bool enableOpenGL)
{
	if (enableOpenGL)
		view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
	else
		view.setViewport(new QWidget());

	view.setScene(m_scene);
	view.setBackgroundBrush(*m_backgroundBrush);
}

void GraphicDrawerQt::configureViews(bool enableOpenGL)
{
	for (vector<QGraphicsView*>::iterator i = m_views.begin(); i != m_views.end(); ++i)
		configureView(**i, enableOpenGL);
}

void GraphicDrawerQt::createBackgroundBrush()
{
	QSvgRenderer renderer(QString("resources/graphics/bg_cell_pattern.svg"));
	QImage image(m_pixelPerMeter, m_pixelPerMeter, QImage::Format_ARGB32);
	QPainter painter(&image);
	renderer.render(&painter);
	m_backgroundBrush = new QBrush(image);
}

void GraphicDrawerQt::updateViewAreas(const GameState &gameState)
{
	for (map<unsigned int, QGraphicsView*>::iterator i = m_playerIDToViewMap.begin(); i != m_playerIDToViewMap.end(); ++i)
		updateViewArea(i->first, *(i->second), gameState);
}

void GraphicDrawerQt::updateViewArea(unsigned int playerID, QGraphicsView &view, const GameState &gameState)
{
	if (gameState.isPlayerAlive(playerID))
	{
		const PlayerState &player = gameState.getPlayerStateById(playerID);
		updateViewPositionForPlayer(player, view);
	}
	else
		fitWholeAreaInView(view);
}

void GraphicDrawerQt::initializeScales()
{
	for (vector<QGraphicsView*>::iterator i = m_views.begin(); i != m_views.end(); ++i)
		m_currentScales.insert(pair<QGraphicsView*, double>(*i, 1));
}

void GraphicDrawerQt::centerViewsOnPlayer(const Common::GameState &gameState)
{
	for (map<unsigned int, QGraphicsView*>::iterator i = m_playerIDToViewMap.begin(); i != m_playerIDToViewMap.end(); ++i)
	{
		const Common::PlayerState &player = gameState.getPlayerStateById(i->first);
		centerViewOnPlayer(*(i->second), player);
	}
}

void GraphicDrawerQt::centerViewOnPlayer(QGraphicsView &view, const PlayerState &player)
{
	Point playerPosition(player.getPosition()*m_pixelPerMeter);
	playerPosition.switchIntoQtCoordinates();
	view.centerOn(playerPosition.toQPoint());
}
