#include "leveldefinition.h"

using namespace Common;
using namespace std;

LevelDefinition::LevelDefinition() :
	m_width(50),
	m_height(50),
	m_objectMatrix(m_width*m_height, ObjectTypeEmpty)
{
	m_objectMatrix[0] = ObjectTypePlayer;
}

LevelDefinition::LevelDefinition(unsigned int width, unsigned int height) :
	m_width(width),
	m_height(height),
	m_objectMatrix(m_width*m_height, ObjectTypeEmpty)
{
	m_objectMatrix[0] = ObjectTypePlayer;
}

LevelDefinition::ObjectType LevelDefinition::getObjectTypeAtPosition(unsigned int positionX, unsigned int positionY) const
{
	return m_objectMatrix[m_width*positionY+positionX];
}

unsigned int LevelDefinition::getLevelHeight() const
{
	return m_height;
}

unsigned int LevelDefinition::getLevelWidth() const
{
	return m_width;
}

void LevelDefinition::setObjectTypeAtPosition(ObjectType objectType, unsigned int positionX, unsigned int positionY)
{
	m_objectMatrix[m_width*positionY+positionX] = objectType;
}

size_t LevelDefinition::getPlayerStartPositionCount() const
{
	size_t result = 0;

	for (vector<ObjectType>::const_iterator i = m_objectMatrix.begin(); i != m_objectMatrix.end(); ++i)
		if (*i == LevelDefinition::ObjectTypePlayer)
			++result;

	return result;
}

LevelDefinition LevelDefinition::createDefaultLevel()
{
	LevelDefinition result(15, 10);

	result.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, 3, 3);
	result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 0, 3);
	result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 4, 7);
	result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 2);
	result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 3, 4);
	result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 2);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 5, 4);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 2);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 7, 4);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 9, 2);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, 9, 4);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 11, 2);
    result.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, 11, 3);

	return result;
}
