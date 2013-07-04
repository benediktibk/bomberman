#ifndef GAMEENGINE_ROUTERGRIDFIELD_H
#define GAMEENGINE_ROUTERGRIDFIELD_H

#include "common/gridpoint.h"

namespace GameEngine
{
	class RouterGridField
	{
	public:
		RouterGridField(const Common::GridPoint &position);
		RouterGridField();

		bool isLooseWall() const;
		bool isSolidWall() const;
		bool isBomb() const;
		bool isPlayer() const;
		bool isDangerous() const;
		bool isFree() const;
		bool isPowerUp() const;
		void setLooseWall(bool value);
		void setSolidWall(bool value);
		void setBomb(bool value);
		void setPlayer(bool value);
		void setDangerous(bool value);
		void setPowerUp(bool value);
		void clear();
		const Common::GridPoint& getPosition() const;
		bool isValid() const;

	private:
		bool m_looseWall;
		bool m_solidWall;
		bool m_bomb;
		bool m_player;
		bool m_dangerous;
		bool m_powerUp;
		Common::GridPoint m_position;
		bool m_valid;
	};
}

#endif
