#ifndef COMMON_GRAPHICDRAWER_H
#define COMMON_GRAPHICDRAWER_H

#include "gamestate.h"

namespace Common
{
class GraphicDrawer
{
public:
	virtual void draw(const GameState &gameState) = 0;

	virtual ~GraphicDrawer() { }
};
}

#endif
