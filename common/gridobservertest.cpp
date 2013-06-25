#include "common/gridobservertest.h"
#include "common/gridobserverstub.h"
#include "common/grid.h"

using namespace Common;

void GridObserverTest::setUp()
{
	m_grid = new Grid(4, 3);
}

void GridObserverTest::tearDown()
{
	delete m_grid;
	m_grid = 0;
}

void GridObserverTest::constructor_validGrid_gridHasObserverCount1()
{
	GridObserverStub *observer = new GridObserverStub(*m_grid);

	CPPUNIT_ASSERT_EQUAL((size_t)1, m_grid->getObserverCount());
	delete observer;
}

void GridObserverTest::destructor_validGrid_gridHasObserverCount0()
{
	GridObserverStub *observer = new GridObserverStub(*m_grid);

	delete observer;

	CPPUNIT_ASSERT_EQUAL((size_t)0, m_grid->getObserverCount());
}
