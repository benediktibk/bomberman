#ifndef COMMON_LEVELDEFINITION_H
#define COMMON_LEVELDEFINITION_H

#include <vector>

namespace Common
{

class LevelDefinition
{
public:
	enum ObjectType
	{
		ObjectTypeEmpty,
		ObjectTypePlayer,
		ObjectTypeSolidWall,
		ObjectTypeLooseWall
	};

	LevelDefinition();

	ObjectType getObjectTypeAtPosition(unsigned int positionX, unsigned int positionY);
	unsigned int getLevelWidth();
	unsigned int getLevelHeight();

private:
	unsigned int m_width;
	unsigned int m_height;
	ObjectType m_objectType;
	std::vector<ObjectType> m_objectMatrix;
};
}

#endif // LEVELDEFINITION_H
