#ifndef PHYSIC_BOMB_H
#define PHYSIC_BOMB_H

namespace Common
{
	class BombState;
	class PlayerState;
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

		void doNotCollideWith(const Common::PlayerState &player);
		void collideWithEverything();

	private:
		StaticObject *m_object;
	};
}

#endif
