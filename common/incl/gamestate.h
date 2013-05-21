#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "playerstate.h"

namespace Common
{
class GameState
{
public:
	void setPlayerState(const PlayerState &state);
	const PlayerState& getPlayerState() const;

private:
	PlayerState m_playerState;
};
}

#endif
