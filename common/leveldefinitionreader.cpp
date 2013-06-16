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
    std::ifstream ifs;
    string textInLine;

    ifs.open ("recources/levels/levellist.csv", std::ifstream::in);
    if(ifs)
    {
        while (!ifs.eof())
        {
            getline(ifs, textInLine);
            if(textInLine.find(levelName) != string::npos)
                break;
        }
    }
    else
        cout << "ERROR Could not open file";

    ifs.close();
}
