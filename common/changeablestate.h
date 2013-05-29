#ifndef COMMON_CHANGEABLESTATE_H
#define COMMON_CHANGEABLESTATE_H

namespace Common
{
class ChangeableState
{
public:
	ChangeableState();
	virtual ~ChangeableState();

public:
	void setChanged();
	bool hasChanged();
	void resetChanged();

private:
	bool m_changed;
};
}

#endif
