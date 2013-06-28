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

		virtual void setAllPossiblePlayerIDs(const std::vector<unsigned int> &playerIDs);
		virtual std::map<unsigned int, Common::InputState> getInputStates();

		unsigned int getCallsToGetInputStates() const;

	private:
		unsigned int m_callsToGetInputState;
	};
}

#endif
