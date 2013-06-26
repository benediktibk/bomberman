#include "gameengine/routergrid.h"
#include "common/grid.h"
#include "common/gamestate.h"
#include <algorithm>

using namespace GameEngine;
using namespace Common;
using namespace std;
using namespace boost;

RouterGrid::RouterGrid(Grid &grid, const GameState &gameState, unsigned int playerID) :
	GridObserver(grid),
	m_grid(grid),
	m_gameState(gameState),
	m_width(grid.getColumns()),
	m_height(grid.getRows()),
	m_fields(extents[m_height][m_width]),
	m_ownPlayerId(playerID)
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			fieldHasChanged(GridPoint(x, y));
}

void RouterGrid::fieldHasChanged(const GridPoint &position)
{
	unsigned int row = position.getY();
	unsigned int column = position.getX();

	assert(column < m_width);
	assert(row < m_height);

	bool player = m_fields[row][column].isPlayer();
	m_fields[row][column].clear();

	if (m_grid.isPlaceCoveredByBomb(position))
		m_fields[row][column].setBomb(true);
	else if (m_grid.isPlaceCoveredByLooseWall(position))
		m_fields[row][column].setLooseWall(true);
	else if (m_grid.isPlaceCoveredBySolidWall(position))
		m_fields[row][column].setSolidWall(true);
	else if (m_grid.isPlaceCoveredByPowerUp(position))
		m_fields[row][column].setPowerUp(true);

	if (m_grid.isPlaceDangerous(position))
		m_fields[row][column].setDangerous(true);

	m_fields[row][column].setPlayer(player);
}

unsigned int RouterGrid::getWidth() const
{
	return m_width;
}

unsigned int RouterGrid::getHeight() const
{
	return m_height;
}

const RouterGridField& RouterGrid::getField(const GridPoint &position) const
{
	assert(position.getX() < m_width);
	assert(position.getY() < m_height);

	return m_fields[position.getY()][position.getX()];
}

void RouterGrid::updatePlayerFlags()
{
	removePlayerFlags();
	vector<GridPoint> playerFields = getAllPlayerFields();

	for (vector<GridPoint>::const_iterator i = playerFields.begin(); i != playerFields.end(); ++i)
	{
		RouterGridField &field = getFieldInternal(*i);
		field.setPlayer(true);
	}
}

RouterGridField& RouterGrid::getFieldInternal(const GridPoint &position)
{
	assert(position.getX() < m_width);
	assert(position.getY() < m_height);

	return m_fields[position.getY()][position.getX()];
}


void RouterGrid::removePlayerFlags()
{
	for (unsigned int x = 0; x < m_width; ++x)
		for (unsigned int y = 0; y < m_height; ++y)
			m_fields[y][x].setPlayer(false);
}

vector<GridPoint> RouterGrid::getAllPlayerFields() const
{
	vector<GridPoint> result;
	vector<const PlayerState*> players = m_gameState.getAllPlayers();

	for (vector<const PlayerState*>::const_iterator i = players.begin(); i != players.end(); ++i)
	{
		if ((*i)->getId() == m_ownPlayerId)
			continue;

		vector<GridPoint> resultPart = m_grid.getPlayerFields(**i);
		result.insert(result.end(), resultPart.begin(), resultPart.end());
	}

	return result;
}
