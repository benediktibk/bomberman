#ifndef PHYSIC_PLAYER_H
#define PHYSIC_PLAYER_H

#include "common/point.h"

namespace Physic
{
class PhysicSimulator;
class DynamicObject;

class Player
{
public:
	Player(PhysicSimulator &simulator, const Common::Point &position, double width, double height);
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

private:
	void updateObjectToPhysicalDimensions(const Common::Point &position);

private:
	PhysicSimulator &m_simulator;
	DynamicObject *m_object;
	double m_width;
	double m_height;
	double m_physicalWidth;
	double m_physicalHeight;
};
}

#endif
