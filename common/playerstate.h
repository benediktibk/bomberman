#ifndef COMMON_PLAYERSTATE_H
#define COMMON_PLAYERSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/destroyablestate.h"
#include <vector>

namespace Common
{
	class BombState;

	class PlayerState :
			public DestroyableState
	{
	public:
		enum PlayerDirection
		{
			PlayerDirectionUp,
			PlayerDirectionDown,
			PlayerDirectionLeft,
			PlayerDirectionRight,
			PlayerDirectionNone
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
		double getSpeed() const;
		void increaseSpeed();
		void increaseMaximumBombRange(unsigned int number);
		double getSpeedIntoX() const;
		double getSpeedIntoY() const;
		void setNotMoving();
		bool isMoving() const;
		double getWidth() const;
		double getHeight() const;
		void setWidth(double value);
		void setHeight(double value);
		bool canPlayerPlaceBomb () const;
		Point getCenterPosition() const;
		void doNotCollideWith(const BombState *bomb);
		std::vector<const BombState*> getBombsNotToCollideWith() const;
		void removeBombFromDoNotCollideList(const BombState *bomb);
		unsigned int getDestructionRangeOfNewBombs() const;
		void setDestructionRangeOfNewBombs(unsigned int value);
        void setPlacedBombAlready(bool value);

	private:
		// forbid copies
		PlayerState(const PlayerState &player);
		void operator=(const PlayerState &player);

	private:
		Point m_position;
		PlayerDirection m_direction;
		unsigned int m_placedBombCount;
		unsigned int m_maxBombs;
		double m_speed;
		const double m_maximumSpeed;
		double m_width;
		double m_height;
		unsigned int m_playerId;
		UniqueIdCreator &m_creatorId;
		std::vector<const Common::BombState*> m_bombsNotToCollideWith;
		unsigned int m_destructionRangeOfNewBombs;
        bool m_placedBombAlready;
	};
}

#endif
