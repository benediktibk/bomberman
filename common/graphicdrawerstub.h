#ifndef COMMON_GRAPHICDRAWERSTUB_H
#define COMMON_GRAPHICDRAWERSTUB_H

#include "common/graphicdrawer.h"

namespace Common
{
	class GraphicDrawerStub :
			public GraphicDrawer
	{
	public:
		virtual void setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs);
		virtual double draw(const GameState &gameState);
	};
}

#endif
