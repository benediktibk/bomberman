#ifndef COMMON_CHANGABLESTATE_H
#define COMMON_CHANGABLESTATE_H

namespace Common
{
class ChangeableState
{
public:
	ChangeableState();

public:
	void setChanged();
	bool hasChanged();
	void resetChanged();

private:
	bool m_changed;
};
}

#endif
