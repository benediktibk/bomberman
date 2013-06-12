#include "common/graphicdrawermock.h"

using namespace Common;

GraphicDrawerMock::GraphicDrawerMock() :
	m_callsToDraw(0),
	m_callsToSetResponsibleForPlayers(0)
{ }

void GraphicDrawerMock::setResponsibleForPlayers(const std::vector<unsigned int> &)
{
	++m_callsToSetResponsibleForPlayers;
}

void GraphicDrawerMock::draw(const GameState &)
{
	++m_callsToDraw;
}

unsigned int GraphicDrawerMock::getCallsToDraw() const
{
	return m_callsToDraw;
}

unsigned int GraphicDrawerMock::getCallsToSetResponsibleForPlayers() const
{
	return m_callsToSetResponsibleForPlayers;
}
