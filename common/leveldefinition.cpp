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
{ }

LevelDefinition::LevelDefinition(const CSVParser &parsedFile) :
	m_width(parsedFile.getWidthOfFile()),
	m_height(parsedFile.getHeightOfFile()),
	m_objectMatrix(m_width*m_height, ObjectTypeEmpty)
{
	std::string objectType;
	m_levelBuildingCorrect = parsedFile.isFileCorrect() && parsedFile.couldOpenFile();
	for (unsigned int y = 0; y < m_height; ++y)
		for (unsigned int x = 0; x < m_width; ++x)
		{
			objectType = parsedFile.getTextInField(x,y);
			if (objectType == "free")
				m_objectMatrix[m_width * y + x] = ObjectTypeEmpty;
			else if(objectType == "loose")
				m_objectMatrix[m_width * y + x] = ObjectTypeLooseWall;
			else if(objectType == "solid")
				m_objectMatrix[m_width * y + x] = ObjectTypeSolidWall;
			else if(objectType == "player")
				m_objectMatrix[m_width * y + x] = ObjectTypePlayer;
			else
				m_levelBuildingCorrect = false;
		}
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

bool LevelDefinition::isLevelBuildingCorrect() const
{
	return m_levelBuildingCorrect;
}
