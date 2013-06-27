#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHERHARD_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHERHARD_H

#include "gameengine/computerenemyinputfetcher.h"

namespace GameEngine
{
	class ComputerEnemyInputFetcherHard :
			public ComputerEnemyInputFetcher
	{
	public:
		ComputerEnemyInputFetcherHard(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerID);

	protected:
		virtual void calculateInputStateInternal();
	};
}

#endif
