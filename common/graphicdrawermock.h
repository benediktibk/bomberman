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

		virtual void draw(const GameState &gameState);

		unsigned int getCallsToDraw() const;

	private:
		unsigned int m_callsToDraw;
	};
}

#endif
