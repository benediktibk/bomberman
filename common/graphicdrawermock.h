#ifndef COMMON_GRAPHICDRAWERMOCK_H
#define COMMON_GRAPHICDRAWERMOCK_H

#include "common/graphicdrawer.h"

namespace Common
{
	class GraphicDrawerMock :
			public GraphicDrawer
	{
	public:
		GraphicDrawerMock();

		virtual void setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs);
		virtual void draw(const GameState &gameState);

		unsigned int getCallsToDraw() const;
		unsigned int getCallsToSetResponsibleForPlayers() const;

	private:
		unsigned int m_callsToDraw;
		unsigned int m_callsToSetResponsibleForPlayers;
	};
}

#endif
