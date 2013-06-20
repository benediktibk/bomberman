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

void RouterGridTest::constructor_gridWith4RowsAnd3Columns_widthIs3()
{
	RouterGrid routerGrid(*m_grid);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, routerGrid.getWidth());
}

void RouterGridTest::constructor_gridWith4RowsAnd3Columns_heightIs4()
{
	RouterGrid routerGrid(*m_grid);

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, routerGrid.getHeight());
}
