#include "allplayerinputfetcher.h"

#include <assert.h>
#include <algorithm>

using namespace Common;

allPlayerInputFetcher::allPlayerInputFetcher(InputFetcher &input, GameEngine::ComputerEnemyInputFetcher* computer):
    m_inputFetcher(input),
  m_computerInputFetcher(computer)
{
}

void allPlayerInputFetcher::setAllPossiblePlayerIds(std::vector<unsigned int> allPossiblePlayerIds)
{
    for(size_t i = 0; i < allPossiblePlayerIds.size(); i++)
        m_playerIds = allPossiblePlayerIds;
}


std::map<unsigned int, InputState> allPlayerInputFetcher::getInputStates()
{
    return m_inputStates;
}

void allPlayerInputFetcher::setGameMode(unsigned int playerCount)
{
    assert(playerCount>0);
    if(playerCount==1)
    {
        m_gameModeIsSinglePlayer=true;
        m_inputStatePlayer1 = m_inputFetcher.getInputState();
        m_inputStatePlayer2 = m_computerInputFetcher->getInputState();  
        m_inputStates[m_playerIds.front()] = m_inputStatePlayer1;
        m_inputStates[m_playerIds.back()] = m_inputStatePlayer2;
                
    } 

    if(playerCount<1)
    {   m_gameModeIsSinglePlayer=false;  
        m_inputStates = m_inputFetcher.getInputStates();     
    }
    
}