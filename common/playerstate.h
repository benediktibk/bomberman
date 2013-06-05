#ifndef COMMON_PLAYERSTATE_H
#define COMMON_PLAYERSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"

namespace Common
{
	class PlayerState
	{
	public:
		enum PlayerDirection
		{
			PlayerDirectionUp,
			PlayerDirectionDown,
			PlayerDirectionLeft,
			PlayerDirectionRight
		};

		PlayerState(UniqueIdCreator &creator);
		~PlayerState();

		void setPosition(Point value);
		Point getPosition() const;
		PlayerDirection getDirection() const;
		unsigned int getId() const;
		void setDirectionUp();
		void setDirectionDown();
		void setDirectionLeft();
		void setDirectionRight();
		void setMaxBombs(unsigned int maxBombs);
		void increaseMaxBombs();
		void increaseMaxBombs(unsigned int number);
		unsigned int getMaxBombs() const;
		unsigned int getRemainingBombs() const;
		void countBomb();
		void reduceBombCount();
		unsigned int getBombCount();
		double getMaximumSpeed() const;
		double getSpeedIntoX() const;
		double getSpeedIntoY() const;
		void setMoving();
		void setNotMoving();
		bool isMoving() const;
		double getWidth() const;
		double getHeight() const;
		bool canPlayerPlaceBomb () const;
		Point getCenterPosition() const;

	private:
		PlayerState(const PlayerState &player);

	private:
		Point m_position;
		PlayerDirection m_direction;
		unsigned int m_placedBombCount;
		unsigned int m_maxBombs;
		double m_maximumSpeed;
		double m_width;
		double m_height;
		unsigned int m_playerId;
		UniqueIdCreator &m_creatorId;
		bool m_moving;
	};
}

#endif
