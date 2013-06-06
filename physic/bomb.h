#ifndef PHYSIC_BOMB_H
#define PHYSIC_BOMB_H

namespace Common
{
	class BombState;
}

namespace Physic
{
	class PhysicSimulator;
	class StaticObject;

	class Bomb
	{
	public:
		Bomb(PhysicSimulator &simulator, const Common::BombState &bomb);
		~Bomb();

	private:
		StaticObject *m_object;
	};
}

#endif
