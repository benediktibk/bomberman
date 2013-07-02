#include "gameengine/allplayerinputfetcher.h"
#include "gameengine/computerenemyinputfetchereasy.h"
#include "gameengine/computerenemyinputfetchermedium.h"
#include "gameengine/computerenemyinputfetcherhard.h"
#include "common/gamestate.h"
#include <assert.h>
#include <algorithm>
#include <vector>

using namespace GameEngine;
using namespace std;
using namespace Common;

AllPlayerInputFetcher::AllPlayerInputFetcher(InputFetcher &humanInput, const Common::GameState &gameState, ComputerEnemyLevel computerEnemyLevel, Grid &grid):
	m_humanInputFetcher(humanInput),
	m_gameState(gameState)
{
	vector<unsigned int> computerEnemyIDs = gameState.getAllNotDestroyedComputerEnemyIDs();
	for (size_t i = 0; i < computerEnemyIDs.size(); ++i)
	{
		switch (computerEnemyLevel)
		{
		case ComputerEnemyLevelEasy:
			m_computerEnemyInputFetchers.push_back(new GameEngine::ComputerEnemyInputFetcherEasy(grid, gameState));
			break;
		case ComputerEnemyLevelMedium:
			m_computerEnemyInputFetchers.push_back(new GameEngine::ComputerEnemyInputFetcherMedium(grid, gameState));
			break;
		case ComputerEnemyLevelHard:
			m_computerEnemyInputFetchers.push_back(new GameEngine::ComputerEnemyInputFetcherHard(grid, gameState));
			break;
		}
	}
}

AllPlayerInputFetcher::~AllPlayerInputFetcher()
{
	for (vector<GameEngine::ComputerEnemyInputFetcher*>::iterator i = m_computerEnemyInputFetchers.begin(); i != m_computerEnemyInputFetchers.end(); ++i)
		delete *i;
	m_computerEnemyInputFetchers.clear();
}

void AllPlayerInputFetcher::setAllPossiblePlayerIDs(const vector<unsigned int> &playerIDs)
{
	vector<unsigned int> computerEnemyIDs = m_gameState.getAllNotDestroyedComputerEnemyIDs();
	vector<unsigned int> humanPlayerIDs = m_gameState.getAllNotDestroyedHumanPlayerIDs();

	assert(computerEnemyIDs.size() + humanPlayerIDs.size() == playerIDs.size());

	m_humanInputFetcher.setAllPossiblePlayerIDs(humanPlayerIDs);

	for (size_t i = 0; i < computerEnemyIDs.size(); ++i)
	{
		assert(count(playerIDs.begin(), playerIDs.end(), computerEnemyIDs[i]));
		vector<unsigned int> playerIDs;
		playerIDs.push_back(computerEnemyIDs[i]);
		m_computerEnemyInputFetchers[i]->setAllPossiblePlayerIDs(playerIDs);
	}

	// make the compiler happy
	(void)playerIDs;
}

map<unsigned int, InputState> AllPlayerInputFetcher::getInputStates()
{
	map<unsigned int, InputState> result = m_humanInputFetcher.getInputStates();

	for (vector<GameEngine::ComputerEnemyInputFetcher*>::iterator i = m_computerEnemyInputFetchers.begin(); i != m_computerEnemyInputFetchers.end(); ++i)
	{
		GameEngine::ComputerEnemyInputFetcher &computerEnemy = **i;
		map<unsigned int, InputState> resultPart = computerEnemy.getInputStates();

		for (map<unsigned int, InputState>::const_iterator j = resultPart.begin(); j != resultPart.end(); ++j)
			result.insert(*j);
	}

	return result;
}