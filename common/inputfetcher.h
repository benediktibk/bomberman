#ifndef COMMON_INPUTFETCHER_H
#define COMMON_INPUTFETCHER_H

#include "inputstate.h"
#include <map>
#include <vector>

namespace Common
{	class InputFetcher

	{
	public:
		virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &playerIDs) = 0;
		virtual std::map<unsigned int, Common::InputState> getInputStates() = 0;
		virtual ~InputFetcher() { }
	};
}
#endif
