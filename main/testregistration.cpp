#include "common/inputstatetest.h"
#include "common/gamestatetest.h"
#include "gameengine/gameengineimpltest.h"
#include "gamelooptest.h"
#include "physic/physicsimulatortest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "common/pointtest.h"
#include "common/gridpointtest.h"
#include "common/enemystatetest.h"
#include "common/bombstatetest.h"
#include "common/wallstatetest.h"
#include "common/uniqueidcreatortest.h"
#include "common/changeablestatetest.h"
#include "gameengine/gridtest.h"
#include "common/destroyablestatetest.h"
#include "common/leveldefinitiontest.h"
#include "physic/physicalobjecttest.h"
#include "physic/dynamicobjecttest.h"
#include "physic/staticobjecttest.h"
#include "common/powerupstatetest.h"
#include "common/powerupmaxbombstatetest.h"
#include "physic/playertest.h"
#include "physic/gamephysicsimulatortest.h"
#include "common/randomdecisiontest.h"
#include "physic/collisiongroupstest.h"
#include "common/powerupgeneratortest.h"
#include "common/playerstatetest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Common::InputStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GameStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GridPointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::EnemyStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::BombStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::WallStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::DestroyableStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::LevelDefinitionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpMaxBombStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::UniqueIdCreatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::ChangeableStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::RandomDecisionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PlayerStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PhysicalObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::DynamicObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::StaticObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PlayerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PhysicSimulatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::CollisionGroupsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::GamePhysicSimulatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::GameEngineImplTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::GridTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Main::GameLoopTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpGeneratorTest);
