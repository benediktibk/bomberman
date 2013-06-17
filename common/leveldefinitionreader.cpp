#include "leveldefinitionreader.h"

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

	csvRead.open ("resources/levels/levellist.csv", std::ifstream::in);
	if(csvRead.is_open())
    {
        while (!csvRead.eof())
        {
            getline(csvRead, textInLine);
            if(textInLine.find(levelName) != string::npos)
                getline(csvRead, m_levelParameters.name, ';');
				getline(csvRead, m_levelParameters.width, ';');
				getline(csvRead, m_levelParameters.height, ';');
				getline(csvRead, m_levelParameters.playerMaximum, ';');
                break;
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
