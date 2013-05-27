#include "inputstatetest.h"
#include "gamestatetest.h"
#include "gameengineimpltest.h"
#include "gamelooptest.h"
#include "physicsimulatortest.h"
#include "threadtest.h"
#include "mutextest.h"
#include "signaltest.h"
#include "stopwatchtest.h"
#include "pointtest.h"
#include "enemystatetest.h"
#include "bombstatetest.h"
#include "wallstatetest.h"
#include "uniqueidcreatortest.h"

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
