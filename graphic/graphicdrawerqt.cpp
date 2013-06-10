#include "graphic/graphicdrawerqt.h"
#include "graphic/player.h"
#include "graphic/wall.h"
#include "graphic/bomb.h"
#include "graphic/powerup.h"
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace Graphic;
using namespace Common;
using namespace std;

GraphicDrawerQt::GraphicDrawerQt(QGraphicsView &view) :
	m_view(view),
	m_scene(new QGraphicsScene()),
	m_pixelPerMeter(40),
	m_firstRedraw(true)
{
	m_scene->setSceneRect(-100, -100, 200, 200);
	m_view.setBackgroundBrush(QBrush(QColor(255, 255, 255)));
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

void GraphicDrawerQt::draw(const GameState &gameState)
{
	if (m_firstRedraw)
		drawBorderWalls(gameState.getGameStateWidth(), gameState.getGameStateHeight());

	drawWalls(gameState.getAllChangedWalls());
	drawBombs(gameState.getAllChangedBombs());
	drawPowerUps(gameState.getAllChangedPowerUps());
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

void GraphicDrawerQt::drawPowerUps(const std::vector<const PowerUpState *> &powerUps)
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

	m_bombs.clear();;
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
