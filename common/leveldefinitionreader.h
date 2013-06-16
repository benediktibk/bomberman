#ifndef COMMON_LEVELDEFINITIONREADER_H
#define COMMON_LEVELDEFINITIONREADER_H

#include <stddef.h>
#include "leveldefinition.h"
#include <iostream>
#include <fstream>
#include <string>

namespace Common
{

class LevelDefinitionReader
{
public:
    struct Level
    {
        std::string levelName;
        unsigned int width;
        unsigned int height;
        unsigned int playerMaximum;
    };

    LevelDefinitionReader();
    LevelDefinition getLoadedLevel() const;
    void readLevelFromLevelList(std::string levelName);

private:
    LevelDefinition m_level;
};
}

#endif // LEVELDEFINITIONREADER_H
