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
        ObjectTypeLooseWall,
        ObjectTypeEnemy,
        ObjectTypeKIEnemy
	};

	LevelDefinition();

    ObjectType getObjectTypeAtPosition(unsigned int positionX, unsigned int positionY);
    unsigned int getLevelWidth() const;
    unsigned int getLevelHeight() const;
    void setObjectTypeAtPosition(ObjectType objectType, unsigned int positionX, unsigned int positionY);

private:
	unsigned int m_width;
	unsigned int m_height;
	ObjectType m_objectType;
	std::vector<ObjectType> m_objectMatrix;
};
}

#endif // LEVELDEFINITION_H
