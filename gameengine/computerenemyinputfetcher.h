#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHER_H

#include "common/inputfetcher.h"
#include "common/inputstate.h"
#include <vector>
#include <map>



namespace GameEngine
{
    class ComputerEnemyInputFetcher :
        public Common::InputFetcher
{

public:
    ComputerEnemyInputFetcher();
    virtual Common::InputState getInputState();
private:
    Common::InputState m_inputState;
};
}
#endif // COMPUTERENEMYINPUTFETCHER_H
