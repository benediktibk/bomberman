#include "common/inputfetchermock.h"

using namespace Common;

InputFetcherMock::InputFetcherMock() :
	m_callsToGetInputState(0)
{ }

InputState InputFetcherMock::getInputState()
{
	++m_callsToGetInputState;
	return InputState();
}

unsigned int InputFetcherMock::getCallsToGetInputState() const
{
	return m_callsToGetInputState;
}

std::map<unsigned int, InputState> InputFetcherMock::getInputStates()
{
    std::map<unsigned int, InputState> result;
    return result;;
}