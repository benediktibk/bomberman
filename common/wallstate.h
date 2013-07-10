#ifndef COMMON_WALLSTATE_H
#define COMMON_WALLSTATE_H

#include "common/point.h"
#include "common/uniqueidcreator.h"
#include "common/changeableanddestroyablestate.h"
namespace Common
{
class WallState :
		public ChangeableAndDestroyableState
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
	double getDimension() const;

private:
	// forbid copies
	WallState(const WallState &wall);
	void operator=(const WallState &wall);

private:
	const Point m_position;
	const unsigned int m_wallId;
	UniqueIdCreator &m_creatorId;
	const WallType m_wallType;
	const double m_dimension;
};
}

#endif

