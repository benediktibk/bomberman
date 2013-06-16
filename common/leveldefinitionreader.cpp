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

/*std::istream& LevelDefinitionReader::readLevel( std::istream& in, Level& level)
{
    istream.getline(in, level.levelName, ';');
    istream.getline( in, level.width, ';');
    istream.getline( in, level.height, ';');
    istream.getline( in, level.playerMaximum, '\n');
    return in;
}
*/
