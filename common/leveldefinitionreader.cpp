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

void LevelDefinitionReader::readLevelFromLevelList(/*string levelName*/)
{
    std::ifstream ifs;

    ifs.open ("levellist.csv", std::ifstream::in);
    if(ifs)
    {
        while (!ifs.eof())
        {
        }
    }
    else
        cout << "";

    ifs.close();
}
