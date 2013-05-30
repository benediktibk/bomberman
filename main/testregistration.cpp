#include "common/inputstatetest.h"
#include "common/gamestatetest.h"
#include "gameengine/gameengineimpltest.h"
#include "gamelooptest.h"
#include "physic/physicsimulatortest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "common/stopwatchtest.h"
#include "common/pointtest.h"
#include "common/enemystatetest.h"
#include "common/bombstatetest.h"
#include "common/wallstatetest.h"
#include "common/uniqueidcreatortest.h"
#include "common/changeablestatetest.h"
#include "gameengine/gridtest.h"
#include "common/destroyablestatetest.h"
#include "common/leveldefinitiontest.h"
#include "physic/dynamicobjecttest.h"
#include "physic/staticobjecttest.h"
#include "common/powerupstatetest.h"
#include "common/powerupmaxbombstatetest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Physic::DynamicObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::StaticObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::InputStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GameStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::StopWatchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::EnemyStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::BombStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::WallStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::GameEngineImplTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Main::GameLoopTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PhysicSimulatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::UniqueIdCreatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::ChangeableStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::GridTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::DestroyableStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::LevelDefinitionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::PowerUpMaxBombStateTest);
