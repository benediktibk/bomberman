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
	std::ifstream csvRead;
    string textInLine;

	csvRead.open("resources/levels/levellist.csv", std::ifstream::in);
	if(csvRead.is_open())
    {
        while (!csvRead.eof())
        {
            getline(csvRead, textInLine);
            if(textInLine.find(levelName) != string::npos)
			{
				getline(csvRead, m_levelParameters.name, ';');
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
	std::ifstream csvRead;
	std::string fileName = std::string("resources/levels/") + m_levelParameters.name + ".csv";
	std::string objectAtPosition;

	csvRead.open(fileName.c_str(), std::ifstream::in);
	if(csvRead.is_open())
	{
		while (!csvRead.eof())
		{
			for (unsigned int x = 0; x < width; ++x)
			{
				for (unsigned int y = 0; y < height; ++y)
				{
					getline(csvRead, objectAtPosition, ';');
					//schleife
				}
			}
		}
	}
	else
		cerr << "ERROR could not read file" << endl;

	csvRead.close();

	m_level = currentLevel;
}
