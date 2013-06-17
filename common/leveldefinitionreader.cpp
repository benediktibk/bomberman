#include "leveldefinitionreader.h"
#include <stdlib.h>

using namespace Common;
using namespace std;

LevelDefinitionReader::LevelDefinitionReader()
{
}

LevelDefinition LevelDefinitionReader::getLoadedLevel() const
{
    return m_level;
}

void LevelDefinitionReader::readLevelFromLevelList(string levelName)
{
	ifstream csvRead("resources/levels/levellist.csv");
    string textInLine;

	if(csvRead.is_open())
    {
		while(!csvRead.eof() && csvRead.good())
        {
			getline(csvRead, textInLine, ';');
            if(textInLine.find(levelName) != string::npos)
			{
				m_levelParameters.name = textInLine;
				getline(csvRead, m_levelParameters.width, ';');
				getline(csvRead, m_levelParameters.height, ';');
				getline(csvRead, m_levelParameters.playerMaximum, ';');
                break;
			}
        }
    }
	else
		cerr << "ERROR could not read file" << endl;

    csvRead.close();
}

const struct LevelDefinitionReader::Level LevelDefinitionReader::getLevelParameters() const
{
	return m_levelParameters;
}

void LevelDefinitionReader::buildLevel()
{
	unsigned int width = atoi(m_levelParameters.width.c_str());
	unsigned int height = atoi(m_levelParameters.height.c_str());
	LevelDefinition currentLevel(width, height);
	ifstream csvRead;
	string fileName = string("resources/levels/") + m_levelParameters.name + ".csv";
	string objectAtPosition;

	csvRead.open(fileName.c_str(), ifstream::in);
	if(csvRead.is_open())
	{
		while (!csvRead.eof())
		{
			for (unsigned int x = 0; x < width; ++x)
			{
				for (int y = (height - 1); y >= 0; --y)
				{
					getline(csvRead, objectAtPosition, ';');
					if(objectAtPosition == "free")
						currentLevel.setObjectTypeAtPosition(LevelDefinition::ObjectTypeEmpty, x, y);
					if(objectAtPosition == "player")
						currentLevel.setObjectTypeAtPosition(LevelDefinition::ObjectTypePlayer, x, y);
					if(objectAtPosition == "loose")
						currentLevel.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, x, y);
					if(objectAtPosition == "solid")
						currentLevel.setObjectTypeAtPosition(LevelDefinition::ObjectTypeSolidWall, x, y);
				}
			}
		}
	}
	else
		cerr << "ERROR could not read file" << endl;

	csvRead.close();

	m_level = currentLevel;
}
