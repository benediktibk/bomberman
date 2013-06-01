#ifndef COMMON_WALLSTATE_H
#define COMMON_WALLSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/changeablestate.h"
#include "common/destroyablestate.h"

namespace Common
{
class WallState :
		public ChangeableState,
		public DestroyableState
{
public:
	enum WallType
	{
		WallTypeSolid,
		WallTypeLoose
	};

	WallState(UniqueIdCreator &creator, WallType wallType, const Point &position);
	~WallState();

	const Point& getPosition() const;
	WallType getWallType() const;
	unsigned int getId() const;
	double getWidth() const;
    double getHeight() const;
private:
    WallState(const WallState &wall);

protected:
	virtual void shouldBeDestroyed();

private:
	const Point m_position;
    const unsigned int m_wallId;
    UniqueIdCreator &m_creatorId;
	const WallType m_wallType;
	double m_width;
	double m_height;
};
}

#endif

