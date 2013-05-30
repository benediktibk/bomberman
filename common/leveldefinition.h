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
	LevelDefinition(unsigned int width, unsigned int height);

	ObjectType getObjectTypeAtPosition(unsigned int positionX, unsigned int positionY) const;
	unsigned int getLevelWidth() const;
	unsigned int getLevelHeight() const;
	void setObjectTypeAtPosition(ObjectType objectType, unsigned int positionX, unsigned int positionY);

	static LevelDefinition createDefaultLevel();

private:
	unsigned int m_width;
	unsigned int m_height;
	ObjectType m_objectType;
	std::vector<ObjectType> m_objectMatrix;
};
}

#endif
