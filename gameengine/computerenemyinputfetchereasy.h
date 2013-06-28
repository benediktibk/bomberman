#ifndef GAMEENGINE_COMPUTERENEMYINPUTFETCHEREASY_H
#define GAMEENGINE_COMPUTERENEMYINPUTFETCHEREASY_H

#include "gameengine/computerenemyinputfetcher.h"

namespace Common
{
	class RandomDecision;
}

namespace GameEngine
{
	class ComputerEnemyInputFetcherEasy :
			public ComputerEnemyInputFetcher
	{
	public:
		ComputerEnemyInputFetcherEasy(Common::Grid &grid, const Common::GameState &gameState);
		virtual ~ComputerEnemyInputFetcherEasy();

	protected:
		virtual void calculateInputStateInternal();

	private:
		Common::RandomDecision *m_getAwayFromDangerousField;
		Common::RandomDecision *m_doSomething;
	};
}

#endif
