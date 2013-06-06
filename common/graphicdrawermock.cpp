#include "common/graphicdrawermock.h"

using namespace Common;

GraphicDrawerMock::GraphicDrawerMock() :
	m_callsToDraw(0)
{ }

void GraphicDrawerMock::draw(const GameState &)
{
	++m_callsToDraw;
}

unsigned int GraphicDrawerMock::getCallsToDraw() const
{
	return m_callsToDraw;
}
