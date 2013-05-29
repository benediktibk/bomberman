#include "leveldefinition.h"

using namespace Common;

LevelDefinition::LevelDefinition() :
    m_width(50),
    m_height(50),
    m_objectMatrix(m_width*m_height,ObjectTypeEmpty)
{ }

LevelDefinition::ObjectType LevelDefinition::getObjectTypeAtPosition(unsigned int positionX, unsigned int positionY)
{
    return m_objectMatrix[m_width*(positionY-1)+positionX-1];
}

