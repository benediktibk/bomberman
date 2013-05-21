#include "gamestate.h"

using namespace Common;

void GameState::setPlayerState(const PlayerState &state)
{
	m_playerState = state;
}

const PlayerState &GameState::getPlayerState() const
{
	return m_playerState;
}
