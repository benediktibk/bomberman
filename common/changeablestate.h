#ifndef CHANGABLESTATE_H
#define CHANGABLESTATE_H

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
