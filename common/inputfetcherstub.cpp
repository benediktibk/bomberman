#include "common/inputfetcherstub.h"

using namespace Common;
using namespace std;

void InputFetcherStub::setAllPossiblePlayerIDs(const vector<unsigned int> &)
{ }

map<unsigned int, InputState> InputFetcherStub::getInputStates()
{
  map<unsigned int, InputState> result;
  return result;
}