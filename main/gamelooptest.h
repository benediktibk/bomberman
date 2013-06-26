#ifndef MAIN_GAMELOOPTEST_H
#define MAIN_GAMELOOPTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace Main
{
class GameLoopTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(GameLoopTest);
	 CPPUNIT_TEST(constructor_notStarted_inputFetcherGotNoCallsToGetInputState);
	 CPPUNIT_TEST(constructor_notStarted_gameEngineGotNoCallsToUpdateGameState);
	 CPPUNIT_TEST(constructor_notStarted_graphicDrawerGotNoCallsToDraw);
	 CPPUNIT_TEST(constructor_notStarted_graphicDrawerGotNoCallsToSetResponsibleForPlayers);
	 CPPUNIT_TEST(execute_runSomeExecutions_inputFetcherGotAsMuchCallsAsGameEngine);
	 CPPUNIT_TEST(execute_runSomeExecutions_gameEngineGotAsMuchCallsAsGraphicDrawer);
	 CPPUNIT_TEST(execute_runAround100ms_gameEngineGotAround6CallsToUpdateGameState);
	 CPPUNIT_TEST(execute_runSomeExecutions_graphicDrawerGotNoCallsToSetResponsibleForPlayers);
	 CPPUNIT_TEST(getFramesPerSecond_running_60);
	 CPPUNIT_TEST(percentageOfTimeNotSleeping_running_0);
	 CPPUNIT_TEST(pause_gameAlreadyRunSomeExecutionsAndWaitOf100ms_callsToMocksDidnotIncrease);
	 CPPUNIT_TEST(pause_gameAlreadyRunSomeExecutions_isPaused);
	 CPPUNIT_TEST(constructor_notStarted_notPaused);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void constructor_notStarted_inputFetcherGotNoCallsToGetInputState();
	 void constructor_notStarted_gameEngineGotNoCallsToUpdateGameState();
	 void constructor_notStarted_graphicDrawerGotNoCallsToDraw();
	 void constructor_notStarted_graphicDrawerGotNoCallsToSetResponsibleForPlayers();
	 void execute_runSomeExecutions_inputFetcherGotAsMuchCallsAsGameEngine();
	 void execute_runSomeExecutions_gameEngineGotAsMuchCallsAsGraphicDrawer();
	 void execute_runAround100ms_gameEngineGotAround6CallsToUpdateGameState();
	 void execute_runSomeExecutions_graphicDrawerGotNoCallsToSetResponsibleForPlayers();
	 void getFramesPerSecond_running_60();
	 void percentageOfTimeNotSleeping_running_0();
	 void pause_gameAlreadyRunSomeExecutionsAndWaitOf100ms_callsToMocksDidnotIncrease();
	 void pause_gameAlreadyRunSomeExecutions_isPaused();
	 void constructor_notStarted_notPaused();
};
}

#endif
