#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHERMEDIUM_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHERMEDIUM_H

#include "gameengine/computerenemyinputfetcher.h"

namespace Common
{
	class RandomDecision;
}

namespace GameEngine
{
	class ComputerEnemyInputFetcherMedium :
			public ComputerEnemyInputFetcher
	{
	public:
		ComputerEnemyInputFetcherMedium(Common::Grid &grid, const Common::GameState &gameState);
		virtual ~ComputerEnemyInputFetcherMedium();

	protected:
		virtual void calculateInputStateInternal();

	private:
		Common::RandomDecision *m_getAwayFromDangerousField;
		Common::RandomDecision *m_doSomething;
	};
}

#endif
