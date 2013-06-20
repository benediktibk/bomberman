#include "gameengine/routergridtest.h"
#include "gameengine/routergrid.h"
#include "gameengine/grid.h"

using namespace GameEngine;

void RouterGridTest::setUp()
{
	m_grid = new Grid(4, 3);
}

void RouterGridTest::tearDown()
{
	delete m_grid;
	m_grid = 0;
}
