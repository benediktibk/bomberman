#ifndef INPUTFETCHER_H
#define INPUTFETCHER_H

#include "inputstate.h"

namespace Common
{
class InputFetcher
{
public:
	virtual InputState getInputState() const = 0;

	virtual ~InputFetcher() { }
};
}
#endif
