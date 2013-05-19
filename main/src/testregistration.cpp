#include "inputstatetest.h"
#include "gamestatetest.h"
#include "gameengineimpltest.h"
#include "gamelooptest.h"
#include "physicsimulatortest.h"
#include "threadtest.h"
#include "mutextest.h"
#include "signaltest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Common::InputStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Common::GameStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(GameEngine::GameEngineImplTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Main::GameLoopTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Physic::PhysicSimulatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::SignalTest);