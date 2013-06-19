#ifndef COMMON_INPUTFETCHER_H
#define COMMON_INPUTFETCHER_H

#include "inputstate.h"
#include <map>

namespace Common
{	class InputFetcher

	{
	public:
        virtual std::map<unsigned int, Common::InputState> getInputStates() = 0;    
		virtual InputState getInputState() = 0;
		virtual ~InputFetcher() { }
	};
}
#endif
