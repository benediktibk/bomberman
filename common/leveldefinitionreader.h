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
		std::string name;
		std::string width;
		std::string height;
		std::string playerMaximum;
	};

	LevelDefinitionReader();
	LevelDefinition getLoadedLevel() const;
	void readLevelFromLevelList(std::string levelName);
	const Level& getLevelParameter() const;
	void buildLevel();

private:
	LevelDefinition m_level;
	Level m_levelParameters;
};
}

#endif // LEVELDEFINITIONREADER_H
