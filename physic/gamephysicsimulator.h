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
	class Wall;
	class Bomb;
	class StaticObject;

	class GamePhysicSimulator
	{
	public:
		GamePhysicSimulator(const Common::LevelDefinition &level);
		~GamePhysicSimulator();

		void simulateStep(Common::GameState &game, double time);
		void updateItems(const Common::GameState &state);

	private:
		void deleteAllWalls();
		void deleteAllBombs();
		void deleteAllPlayers();
		void updateBombs(const Common::GameState &state);
		void updateBomb(const Common::BombState *bomb);
		void updateWalls(const Common::GameState &state);
		void updateWall(const Common::WallState *wall);
		void updateCollisionGroups(const Common::GameState &state);
		void updateCollisionGroupsForPlayer(const Common::PlayerState &player);
		void updatePlayers(const Common::GameState &state);
		void updatePlayer(const Common::PlayerState &player);

	private:
		Physic::PhysicSimulator *m_simulator;
		Physic::StaticObject *m_upperBorder;
		Physic::StaticObject *m_lowerBorder;
		Physic::StaticObject *m_leftBorder;
		Physic::StaticObject *m_rightBorder;
		std::map<const Common::PlayerState*, Player*> m_players;
		std::map<const Common::WallState*, Wall*> m_walls;
		std::map<const Common::BombState*, Bomb*> m_bombs;
	};
}

#endif
