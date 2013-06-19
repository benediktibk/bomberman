#include "allplayerinputfetcher.h"

#include <assert.h>
#include <algorithm>
#include <vector>

using namespace Common;
using namespace std ;



allPlayerInputFetcher::allPlayerInputFetcher(InputFetcher &input,vector<GameEngine::ComputerEnemyInputFetcher*> computer):
    m_inputFetcher(input),
    CompInputFetcher(computer)
{
}

void allPlayerInputFetcher::setAllPossiblePlayerIds(vector<unsigned int> allPossiblePlayerIds)
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
        
        for(vector<GameEngine::ComputerEnemyInputFetcher*>::const_iterator i = CompInputFetcher.begin(); i != CompInputFetcher.end(); ++i)
        {           
            m_computerInputStates.push_back((*i)->getInputState());  
        }
        
        //ID anders implementieren        
        //ID auch auf Enemies 
        //Enemies in m_inputStates pushen
        m_inputStates[m_playerIds.front()] = m_inputStatePlayer1;
        m_inputStates[m_playerIds.back()] = m_inputStatePlayer2;
                
    } 

    if(playerCount>1)
    {   
        m_gameModeIsSinglePlayer=false;  
        m_inputStates = m_inputFetcher.getInputStates();  
        for(vector<GameEngine::ComputerEnemyInputFetcher*>::const_iterator i = CompInputFetcher.begin(); i != CompInputFetcher.end(); ++i)
        {           
            m_computerInputStates.push_back((*i)->getInputState());  
        }
    }
    
}