#ifndef COMMON_ALLPLAYERINPUTFETCHER_H
#define COMMON_ALLPLAYERINPUTFETCHER_H

#include "common/inputstate.h"
#include "common/inputfetcher.h"
#include "gameengine/computerenemyinputfetcher.h"
namespace Common 
{


    class allPlayerInputFetcher:
            public InputFetcher
    {
    public:
    allPlayerInputFetcher(InputFetcher &input,std::vector<GameEngine::ComputerEnemyInputFetcher*> computer );
        
    virtual std::map<unsigned int, InputState> getInputStates();
    virtual Common::InputState getInputState();     
    void setGameMode(unsigned int playerCount);
    void setAllPossiblePlayerIds(std::vector<unsigned int> allPossiblePlayerIds);
    Common::InputState getInputStateByID( unsigned int playerID);
        
    private:   
    std::map<unsigned int, InputState> m_inputStates;
    Common::InputState m_inputStatePlayers; 
    Common::InputState m_inputStateEnemies;
    Common::InputFetcher &m_inputFetcher;
	std::vector<GameEngine::ComputerEnemyInputFetcher*> m_compInputFetcher;
    std::vector<Common::InputState> m_computerInputStates;    
    std::vector<unsigned int> m_playerIds;
    bool m_gameModeIsSinglePlayer;

    };    
}   


#endif // ALLPLAYERINPUTFETCHER_H
