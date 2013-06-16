#ifndef COMMON_LEVELDEFINITIONREADER_H
#define COMMON_LEVELDEFINITIONREADER_H

#include <stddef.h>
#include "leveldefinition.h"

namespace Common
{

class LevelDefinitionReader
{
public:
    LevelDefinitionReader();
    LevelDefinition getLoadedLevel() const;

private:
    LevelDefinition m_level;
};
}

#endif // LEVELDEFINITIONREADER_H
