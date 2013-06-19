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
    allPlayerInputFetcher(InputFetcher &input, GameEngine::ComputerEnemyInputFetcher* computer );
        
    virtual std::map<unsigned int, InputState> getInputStates();
    virtual Common::InputState getInputState();     
    void setGameMode(unsigned int playerCount);
    void setAllPossiblePlayerIds(std::vector<unsigned int> allPossiblePlayerIds);        
        
    private:   
    std::map<unsigned int, InputState> m_inputStates;
    Common::InputState m_inputStatePlayer1;
    Common::InputState m_inputStatePlayer2;
    Common::InputFetcher &m_inputFetcher;
    GameEngine::ComputerEnemyInputFetcher* m_computerInputFetcher;    
    std::vector<unsigned int> m_playerIds;
    bool m_gameModeIsSinglePlayer;

    };    
}   


#endif // ALLPLAYERINPUTFETCHER_H
