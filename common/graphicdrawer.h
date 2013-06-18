#ifndef COMMON_GRAPHICDRAWER_H
#define COMMON_GRAPHICDRAWER_H

#include "common/gamestate.h"

namespace Common
{
	class GraphicDrawer
	{
	public:
		virtual void setResponsibleForPlayers(const std::vector<unsigned int> &playerIDs) = 0;
		virtual void draw(const GameState &gameState) = 0;

		virtual ~GraphicDrawer() { }
	};
}

#endif
