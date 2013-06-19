#ifndef COMMON_LEVELDEFINITION_H
#define COMMON_LEVELDEFINITION_H

#include <vector>
#include <stddef.h>
#include "csvparser.h"

namespace Common
{

class LevelDefinition
{
	public:
		/// @todo are all types used?
		enum ObjectType
		{
			ObjectTypeEmpty,
			ObjectTypePlayer,
			ObjectTypeSolidWall,
			ObjectTypeLooseWall,
			ObjectTypeEnemy,
			ObjectTypeKIEnemy
		};

		LevelDefinition();
		LevelDefinition(unsigned int width, unsigned int height);
		LevelDefinition(const CSVParser &parsedFile);

		ObjectType getObjectTypeAtPosition(unsigned int positionX, unsigned int positionY) const;
		unsigned int getLevelWidth() const;
		unsigned int getLevelHeight() const;
		void setObjectTypeAtPosition(ObjectType objectType, unsigned int positionX, unsigned int positionY);
		size_t getPlayerStartPositionCount() const;
		bool isLevelBuildingCorrect() const;

		static LevelDefinition createDefaultLevel();

	private:
		unsigned int m_width;
		unsigned int m_height;
		std::vector<ObjectType> m_objectMatrix;
		bool m_levelBuildingCorrect;
	};
}

#endif
