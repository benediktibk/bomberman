#include "common/inputstatetest.h"
#include "common/gamestatetest.h"
#include "common/pointtest.h"
#include "common/gridpointtest.h"
#include "common/bombstatetest.h"
#include "common/wallstatetest.h"
#include "common/uniqueidcreatortest.h"
#include "common/changeablestatetest.h"
#include "common/explodedbombstatetest.h"
#include "common/destroyablestatetest.h"
#include "common/leveldefinitiontest.h"
#include "common/powerupgeneratortest.h"
#include "common/playerstatetest.h"
#include "common/powerupmaxvelocitystatetest.h"
#include "common/comparetest.h"
#include "common/csvparsertest.h"
#include "common/powerupmaxbombrangestatetest.h"
#include "common/randomdecisiontest.h"
#include "common/powerupstatetest.h"
#include "common/powerupmaxbombstatetest.h"
#include "physic/physicalobjecttest.h"
#include "physic/dynamicobjecttest.h"
#include "physic/staticobjecttest.h"
#include "physic/playertest.h"
#include "physic/bombtest.h"
#include "physic/gamephysicsimulatortest.h"
#include "physic/collisiongroupstest.h"
#include "physic/physicsimulatortest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "gameengine/gameengineimpltest.h"
#include "common/gridtest.h"
#include "common/gridobservertest.h"
#include "gameengine/routergridfieldtest.h"
#include "gameengine/routergridtest.h"
#include "gameengine/notdangerousandfreedecidertest.h"
#include "gameengine/coveredbyplayerdecidertest.h"
#include "gameengine/coveredbyloosewalldecidertest.h"
#include "gameengine/coveredbypowerupdecidertest.h"
#include "gameengine/freedecidertest.h"
#include "gameengine/routetest.h"
#include "gameengine/routertest.h"
#include "gameengine/computerenemyinputfetcherhardtest.h"
#include "main/gamelooptest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Common::InputStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GameStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GridPointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::BombStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::WallStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::DestroyableStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::LevelDefinitionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpMaxBombStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpMaxBombRangeStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::UniqueIdCreatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::ChangeableStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::RandomDecisionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PlayerStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::ExplodedBombStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpGeneratorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpMaxVelocityStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::CSVParserTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GridTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GridObserverTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PhysicalObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::DynamicObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::StaticObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PlayerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::BombTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PhysicSimulatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::CollisionGroupsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::GamePhysicSimulatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::GameEngineImplTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::RouterGridFieldTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::RouterGridTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::NotDangerousAndFreeDeciderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::CoveredByPlayerDeciderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::CoveredByLooseWallDeciderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::CoveredByPowerUpDeciderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::FreeDeciderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::RouteTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::RouterTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::ComputerEnemyInputFetcherHardTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Main::GameLoopTest);
