#ifndef COMMON_INPUTFETCHERSTUB_H
#define COMMON_INPUTFETCHERSTUB_H

#include "common/inputfetcher.h"
#include "common/inputstate.h"

namespace Common
{
	class InputFetcherStub :
			public InputFetcher
	{
	public:
		virtual InputState getInputState();
	};
}

#endif