#include "common/inputfetcherstub.h"

using namespace Common;

InputState InputFetcherStub::getInputState()
{
	return InputState();
}

std::map<unsigned int, InputState> InputFetcherStub::getInputStates()
{
  std::map<unsigned int, InputState> result;
  return result;
}