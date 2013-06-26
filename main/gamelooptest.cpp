#include "main/gamelooptest.h"
#include "main/gameloop.h"
#include "common/inputfetcherstub.h"
#include "common/inputfetchermock.h"
#include "common/gameenginestub.h"
#include "common/gameenginemock.h"
#include "common/graphicdrawerstub.h"
#include "common/graphicdrawermock.h"
#include <unistd.h>

using namespace Main;
using namespace Common;

void GameLoopTest::constructor_notStarted_inputFetcherGotNoCallsToGetInputState()
{
	InputFetcherMock inputFetcher;
	GameEngineStub gameEngine;
	GraphicDrawerStub graphicDrawer;

	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, inputFetcher.getCallsToGetInputState());
	gameLoop->start();
	gameLoop->stop();
	delete gameLoop;
}

void GameLoopTest::constructor_notStarted_gameEngineGotNoCallsToUpdateGameState()
{
	InputFetcherStub inputFetcher;
	GameEngineMock gameEngine;
	GraphicDrawerStub graphicDrawer;

	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, gameEngine.getCallsToUpdateGameState());
	gameLoop->start();
	gameLoop->stop();
	delete gameLoop;
}

void GameLoopTest::constructor_notStarted_graphicDrawerGotNoCallsToDraw()
{
	InputFetcherStub inputFetcher;
	GameEngineStub gameEngine;
	GraphicDrawerMock graphicDrawer;

	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, graphicDrawer.getCallsToDraw());
	gameLoop->start();
	gameLoop->stop();
	delete gameLoop;
}

void GameLoopTest::constructor_notStarted_graphicDrawerGotNoCallsToSetResponsibleForPlayers()
{
	InputFetcherStub inputFetcher;
	GameEngineStub gameEngine;
	GraphicDrawerMock graphicDrawer;

	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, graphicDrawer.getCallsToSetResponsibleForPlayers());
	gameLoop->start();
	gameLoop->stop();
	delete gameLoop;
}

void GameLoopTest::execute_runSomeExecutions_inputFetcherGotAsMuchCallsAsGameEngine()
{
	InputFetcherMock inputFetcher;
	GameEngineMock gameEngine;
	GraphicDrawerStub graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);
	gameLoop->stop();
	gameLoop->waitTillFinished();

	CPPUNIT_ASSERT_EQUAL(inputFetcher.getCallsToGetInputState(), gameEngine.getCallsToUpdateGameState());
	delete gameLoop;
}

void GameLoopTest::execute_runSomeExecutions_gameEngineGotAsMuchCallsAsGraphicDrawer()
{
	InputFetcherStub inputFetcher;
	GameEngineMock gameEngine;
	GraphicDrawerMock graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);
	gameLoop->stop();
	gameLoop->waitTillFinished();

	CPPUNIT_ASSERT_EQUAL(graphicDrawer.getCallsToDraw(), gameEngine.getCallsToUpdateGameState());
	delete gameLoop;
}

void GameLoopTest::execute_runAround100ms_gameEngineGotAround6CallsToUpdateGameState()
{
	InputFetcherStub inputFetcher;
	GameEngineMock gameEngine;
	GraphicDrawerStub graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);
	gameLoop->stop();
	gameLoop->waitTillFinished();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, gameEngine.getCallsToUpdateGameState(), 1);
	delete gameLoop;
}

void GameLoopTest::execute_runSomeExecutions_graphicDrawerGotNoCallsToSetResponsibleForPlayers()
{
	InputFetcherStub inputFetcher;
	GameEngineStub gameEngine;
	GraphicDrawerMock graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);
	gameLoop->stop();
	gameLoop->waitTillFinished();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, graphicDrawer.getCallsToSetResponsibleForPlayers());
	delete gameLoop;
}

void GameLoopTest::getFramesPerSecond_running_60()
{
	InputFetcherStub inputFetcher;
	GameEngineStub gameEngine;
	GraphicDrawerStub graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(60, gameLoop->getFramesPerSecond(), 1);
	gameLoop->stop();
	gameLoop->waitTillFinished();
	delete gameLoop;
}

void GameLoopTest::percentageOfTimeNotSleeping_running_0()
{
	InputFetcherStub inputFetcher;
	GameEngineStub gameEngine;
	GraphicDrawerStub graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, gameLoop->percentageOfTimeNotSleeping(), 0.1);
	gameLoop->stop();
	gameLoop->waitTillFinished();
	delete gameLoop;
}

void GameLoopTest::pause_gameAlreadyRunSomeExecutionsAndWaitOf100ms_callsToMocksDidnotIncrease()
{
	InputFetcherMock inputFetcher;
	GameEngineMock *gameEngine = new GameEngineMock();
	GraphicDrawerMock graphicDrawer;
	GameLoop *gameLoop = new GameLoop(inputFetcher, *gameEngine, graphicDrawer);

	gameLoop->start();
	usleep(1000*100);
	gameLoop->pause();
	usleep(1000*100);
	unsigned int previousCallsToGetInputState = inputFetcher.getCallsToGetInputState();
	unsigned int previousCallsToUpdateGameState = gameEngine->getCallsToUpdateGameState();
	unsigned int previousCallsToDraw = graphicDrawer.getCallsToDraw();
	usleep(1000*100);
	gameLoop->stop();
	gameLoop->waitTillFinished();

	CPPUNIT_ASSERT_EQUAL(previousCallsToGetInputState, inputFetcher.getCallsToGetInputState());
	CPPUNIT_ASSERT_EQUAL(previousCallsToUpdateGameState, gameEngine->getCallsToUpdateGameState());
	CPPUNIT_ASSERT_EQUAL(previousCallsToDraw, graphicDrawer.getCallsToDraw());
	delete gameLoop;
	delete gameEngine;
}
