#ifndef COMMON_INPUTFETCHER_H
#define COMMON_INPUTFETCHER_H

#include "inputstate.h"

namespace Common
{
	class InputFetcher
	{
	public:
		virtual InputState getInputState() = 0;

		virtual ~InputFetcher() { }
	};
}
#endif
