#ifndef GRAPHICDRAWERQT_H
#define GRAPHICDRAWERQT_H

#include "graphicdrawer.h"

namespace Graphic
{
class GraphicDrawerQt :
		public Common::GraphicDrawer
{
public:
	virtual void draw(const Common::GameState &gameState);

private:
};
}

#endif
