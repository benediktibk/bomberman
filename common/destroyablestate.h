#ifndef COMMON_DESTROYABLESTATE_H
#define COMMON_DESTROYABLESTATE_H

namespace Common
{
class DestroyableState
{
public:
	DestroyableState();
	virtual ~DestroyableState();

	virtual bool isDestroyed() const;
	virtual void setDestroyed();

protected:
	virtual void shouldBeDestroyed();

private:
	bool m_destroyed;
};
}

#endif
