#include "leveldefinition.h"

using namespace Common;

LevelDefinition::LevelDefinition() :
	m_width(50),
	m_height(50),
	m_objectMatrix(m_width*m_height, ObjectTypeEmpty)
{ }

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
