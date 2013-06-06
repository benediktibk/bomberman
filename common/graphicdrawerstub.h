#ifndef COMMON_GRAPHICDRAWERSTUB_H
#define COMMON_GRAPHICDRAWERSTUB_H

#include "common/graphicdrawer.h"

namespace Common
{
	class GraphicDrawerStub :
			public GraphicDrawer
	{
	public:
		virtual void draw(const GameState &gameState);
	};
}

#endif
