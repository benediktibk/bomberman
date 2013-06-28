#include "allplayerinputfetcher.h"
#include <assert.h>
#include <algorithm>
#include <vector>

using namespace Common;
using namespace std;

allPlayerInputFetcher::allPlayerInputFetcher(InputFetcher &input, vector<GameEngine::ComputerEnemyInputFetcher*> computer, size_t playerCount):
	m_inputFetcher(input),
	m_compInputFetcher(computer)
{ 
    if(playerCount==1)
        m_gameModeIsSinglePlayer = true;
    if(playerCount==2)
        m_gameModeIsSinglePlayer = false;
}

void allPlayerInputFetcher::setAllPossiblePlayerIDs(const std::vector<unsigned int> &/*playerIDs*/)
{ }

void allPlayerInputFetcher::setAllPossiblePlayerIds(vector<unsigned int> allPossiblePlayerIds)
{
	for(size_t i = 0; i < allPossiblePlayerIds.size(); i++)
		m_playerIds = allPossiblePlayerIds;
}


map<unsigned int, InputState> allPlayerInputFetcher::getInputStates()
{
	map<unsigned int, InputState> result = m_inputFetcher.getInputStates();
    if(m_gameModeIsSinglePlayer == true)
    {
        result.erase(result.end());
    }

	for (vector<GameEngine::ComputerEnemyInputFetcher*>::iterator i = m_compInputFetcher.begin(); i != m_compInputFetcher.end(); ++i)
	{
		GameEngine::ComputerEnemyInputFetcher &computerEnemy = **i;
		map<unsigned int, InputState> resultPart = computerEnemy.getInputStates();

		for (map<unsigned int, InputState>::const_iterator j = resultPart.begin(); j != resultPart.end(); ++j)
			result.insert(*j);
	}

	return result;
}


Common::InputState allPlayerInputFetcher::getInputStateByID(unsigned int playerID)
{
	return m_inputStates.at(playerID);
}
