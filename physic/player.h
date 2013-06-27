#ifndef PHYSIC_PLAYER_H
#define PHYSIC_PLAYER_H

#include "common/point.h"
#include "common/gridpoint.h"
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
		double getDimension() const;
		double getPhysicalWidth() const;
		double getPhysicalHeight() const;
		bool isMoving() const;
		void updateObstacle();

	private:
		void updateObjectToPhysicalDimensions(const Common::Point &position, int16_t collisionGroup);

	private:
		PhysicSimulator &m_simulator;
		PhysicalObject *m_object;
		DynamicObject *m_dynamicObject;
		StaticObject *m_staticObject;
		StaticObject *m_field1;
		StaticObject *m_field2;
		const double m_dimension;
		double m_physicalWidth;
		double m_physicalHeight;
		bool m_movingIntoX;
		bool m_movingIntoY;
	   int16_t m_collisionGroup;
	};
}

#endif
