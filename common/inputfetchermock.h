#ifndef COMMON_INPUTFETCHERMOCK_H
#define COMMON_INPUTFETCHERMOCK_H

#include "common/inputfetcher.h"
#include "common/inputstate.h"

namespace Common
{
	class InputFetcherMock :
			public InputFetcher
	{
	public:
		InputFetcherMock();

		virtual InputState getInputState();

		unsigned int getCallsToGetInputState() const;

	private:
		unsigned int m_callsToGetInputState;
	};
}

#endif
