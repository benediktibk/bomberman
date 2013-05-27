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