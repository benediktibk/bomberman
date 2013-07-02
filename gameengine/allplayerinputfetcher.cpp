#include "gameengine/allplayerinputfetcher.h"
#include <assert.h>
#include <algorithm>
#include <vector>

using namespace GameEngine;
using namespace std;
using namespace Common;

AllPlayerInputFetcher::AllPlayerInputFetcher(InputFetcher &humanInput, vector<GameEngine::ComputerEnemyInputFetcher*> computer):
	m_humanInputFetcher(humanInput),
	m_compInputFetcher(computer)
{ }

void AllPlayerInputFetcher::setAllPossiblePlayerIDs(const std::vector<unsigned int> &/*playerIDs*/)
{ }

map<unsigned int, InputState> AllPlayerInputFetcher::getInputStates()
{
	map<unsigned int, InputState> result = m_humanInputFetcher.getInputStates();

	for (vector<GameEngine::ComputerEnemyInputFetcher*>::iterator i = m_compInputFetcher.begin(); i != m_compInputFetcher.end(); ++i)
	{
		GameEngine::ComputerEnemyInputFetcher &computerEnemy = **i;
		map<unsigned int, InputState> resultPart = computerEnemy.getInputStates();

		for (map<unsigned int, InputState>::const_iterator j = resultPart.begin(); j != resultPart.end(); ++j)
			result.insert(*j);
	}

	return result;
}