#include "common/inputfetchermock.h"

using namespace Common;

InputFetcherMock::InputFetcherMock() :
	m_callsToGetInputState(0)
{ }

void InputFetcherMock::setAllPossiblePlayerIDs(const std::vector<unsigned int> &)
{ }

unsigned int InputFetcherMock::getCallsToGetInputStates() const
{
	return m_callsToGetInputState;
}

std::map<unsigned int, InputState> InputFetcherMock::getInputStates()
{
	++m_callsToGetInputState;
	std::map<unsigned int, InputState> result;
	return result;;
}