#ifndef COMMON_DESTROYABLESTATE_H
#define COMMON_DESTROYABLESTATE_H

namespace Common
{
class DestroyableState
{
public:
	DestroyableState();

	bool isDestroyed() const;
	void setDestroyed();

protected:
	virtual void gotCallToDestroyed();

private:
	bool m_destroyed;
};
}

#endif
