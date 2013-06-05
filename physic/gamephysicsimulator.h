#ifndef PHYSIC_GAMEPHYSICSIMULATOR_H
#define PHYSIC_GAMEPHYSICSIMULATOR_H

#include <map>

namespace Common
{
	class GameState;
	class WallState;
	class BombState;
	class PlayerState;
	class LevelDefinition;
}

namespace Physic
{
	class PhysicSimulator;
	class Player;
	class StaticObject;
	class CollisionGroups;

	class GamePhysicSimulator
	{
	public:
		GamePhysicSimulator(const Common::LevelDefinition &level, const Common::PlayerState &player);
		~GamePhysicSimulator();

		void simulateStep(Common::PlayerState &player, double time);
		void updateItems(const Common::GameState &state);

	private:
		void deleteAllWallObjects();
		void deleteAllBombObjects();
		void updateBombs(const Common::GameState &state);
		void updateBomb(const Common::BombState *bomb);
		void updateWalls(const Common::GameState &state);
		void updateWall(const Common::WallState *wall);

	private:
		Physic::PhysicSimulator *m_simulator;
		Physic::Player *m_player;
		Physic::StaticObject *m_upperBorder;
		Physic::StaticObject *m_lowerBorder;
		Physic::StaticObject *m_leftBorder;
		Physic::StaticObject *m_rightBorder;
		std::map<const Common::WallState*, Physic::StaticObject*> m_wallObjects;
		std::map<const Common::BombState*, Physic::StaticObject*> m_bombObjects;
	};
}

#endif
