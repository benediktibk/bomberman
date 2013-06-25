#ifndef GAMEENGINE_ROUTERGRID_H
#define GAMEENGINE_ROUTERGRID_H

#include <boost/multi_array.hpp>
#include "common/gridobserver.h"
#include "gameengine/routergridfield.h"

namespace Common
{
	class GameState;
}

namespace GameEngine
{
	class RouterGrid :
			public Common::GridObserver
	{
	private:
		typedef boost::multi_array<RouterGridField, 2> GridFieldMatrix;

	public:
		RouterGrid(Common::Grid &grid, const Common::GameState &gameState, unsigned int playerID);

		virtual void fieldHasChanged(const Common::GridPoint &position);
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		const RouterGridField& getField(const Common::GridPoint &position) const;
		void updatePlayerFlags();

	private:
		RouterGridField& getFieldInternal(const Common::GridPoint &position);
		void markFieldsAsDangerousIfCoveredByBomb(const Common::GridPoint &position);
		void updateFieldInternal(const Common::GridPoint &position);
		void removeDangerousFlags();
		void updateDangerousFlags();
		void removePlayerFlags();
		std::vector<Common::GridPoint> getAllPlayerFields() const;

	private:
		const Common::Grid &m_grid;
		const Common::GameState &m_gameState;
		unsigned int m_width;
		unsigned int m_height;
		GridFieldMatrix m_fields;
		unsigned int m_ownPlayerId;
	};
}

#endif
