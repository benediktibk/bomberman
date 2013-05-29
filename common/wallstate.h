#ifndef COMMON_WALLSTATE_H
#define COMMON_WALLSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/changeablestate.h"

namespace Common
{
class WallState :
		public ChangeableState
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

private:
	const Point m_position;
	const unsigned int m_wallid;
	UniqueIdCreator &m_creatorid;
	const WallType m_wallType;
};
}

#endif

