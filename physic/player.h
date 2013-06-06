#ifndef PHYSIC_PLAYER_H
#define PHYSIC_PLAYER_H

#include "common/point.h"
#include <stdint.h>

namespace Common
{
	class PlayerState;
}

namespace Physic
{
	class PhysicSimulator;
	class PhysicalObject;
	class DynamicObject;
	class StaticObject;

	class Player
	{
	public:
		Player(PhysicSimulator &simulator, const Common::PlayerState &player);
		~Player();

		Common::Point getPosition() const;
		Common::Point getCenterPosition() const;
		void applyLinearVelocity(double velocityIntoX, double velocityIntoY);
		double getVelocityX() const;
		double getVelocityY() const;
		double getWidth() const;
		double getHeight() const;
		double getPhysicalWidth() const;
		double getPhysicalHeight() const;
		bool isMoving() const;

	private:
		void updateObjectToPhysicalDimensions(const Common::Point &position, int16_t collisionGroup);

	private:
		PhysicSimulator &m_simulator;
		PhysicalObject *m_object;
		DynamicObject *m_dynamicObject;
		StaticObject *m_staticObject;
		double m_width;
		double m_height;
		double m_physicalWidth;
		double m_physicalHeight;
		bool m_movingIntoX;
		bool m_movingIntoY;
	};
}

#endif
