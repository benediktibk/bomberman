#include "allplayerinputfetcher.h"

#include <assert.h>
#include <algorithm>
#include <vector>

using namespace Common;
using namespace std ;



allPlayerInputFetcher::allPlayerInputFetcher(InputFetcher &input,vector<GameEngine::ComputerEnemyInputFetcher*> computer):
    m_inputFetcher(input),
	m_compInputFetcher(computer)
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

void allPlayerInputFetcher::setGameMode(unsigned int humanPlayerCount)
{
    assert(humanPlayerCount>0);
    if(humanPlayerCount==1)
    {
        m_gameModeIsSinglePlayer=true;
        m_inputStatePlayers = m_inputFetcher.getInputState();
        
		for(vector<GameEngine::ComputerEnemyInputFetcher*>::const_iterator i = m_compInputFetcher.begin(); i != m_compInputFetcher.end(); ++i)
        {           
            m_computerInputStates.push_back((*i)->getInputState());  
        }
        
        //ID der Player aus MainwindowInputFetcher übernommen
        //ID anders implementieren        
        //ID auch auf Enemies 
        //Enemies in m_inputStates pushen 
        // klasse in Gameloop implementieren
        
        // auf die art id der humanplayer in inpustate gekoppelt
        
        m_inputStates[m_playerIds.front()] = m_inputStatePlayers;
        m_inputStates[m_playerIds.back()] = m_inputStateEnemies; 
                
    } 

    if(humanPlayerCount>1) // in progress
    {   
        m_gameModeIsSinglePlayer=false;  
        m_inputStates = m_inputFetcher.getInputStates();  
		for(vector<GameEngine::ComputerEnemyInputFetcher*>::const_iterator i = m_compInputFetcher.begin(); i != m_compInputFetcher.end(); ++i)
        {           
            m_computerInputStates.push_back((*i)->getInputState());  
        }
    }
    
}

Common::InputState allPlayerInputFetcher::getInputStateByID(unsigned int playerID)
{
    return m_inputStates.at(playerID);
}
