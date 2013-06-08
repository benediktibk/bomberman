#ifndef PHYSIC_WALL_H
#define PHYSIC_WALL_H

namespace Common
{
	class WallState;
}

namespace Physic
{
	class PhysicSimulator;
	class StaticObject;

	class Wall
	{
	public:
		Wall(PhysicSimulator &simulator, const Common::WallState &wall);
		~Wall();

	private:
		StaticObject *m_object;
	};
}

#endif
