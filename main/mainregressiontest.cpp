#include "common/randomdecision.h"
#include "gameengine/gameengineimpl.h"
#include "common/leveldefinition.h"
#include <stdlib.h>
#include <map>

using namespace Common;
using namespace GameEngine;
using namespace std;

LevelDefinition createRandomLevel()
{
	LevelDefinition level(46, 53);
	RandomDecision placeItem(0.1);

	for (unsigned int x = 0; x < level.getLevelHeight(); ++x)
		for (unsigned int y = 0; y < level.getLevelWidth(); ++y)
			if (placeItem.decide())
				level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeLooseWall, x, y);

	level.setObjectTypeAtPosition(LevelDefinition::ObjectTypeEmpty, 0, 0);

	return level;
}

int main(int, char**)
{
	srand(3);
	LevelDefinition level(createRandomLevel());
	GameEngineImpl gameEngine(level, 1);
	RandomDecision pressRight(0.3);
	RandomDecision pressLeft(0.3);
	RandomDecision pressUp(0.3);
	RandomDecision pressDown(0.3);
	InputState input;
	map<unsigned int, InputState> inputs;
	unsigned int playerID = gameEngine.getAllPossiblePlayerIDs().front();

	while(true)
	{
		if (pressRight.decide())
			input.setRightKeyPressed();
		else
			input.setRightKeyNotPressed();

		if (pressLeft.decide())
			input.setLeftKeyPressed();
		else
			input.setLeftKeyNotPressed();

		if (pressUp.decide())
			input.setUpKeyPressed();
		else
			input.setUpKeyNotPressed();

		if (pressDown.decide())
			input.setDownKeyPressed();
		else
			input.setDownKeyNotPressed();

		inputs[playerID] = input;
		gameEngine.updateGameState(inputs, 0.0234);
	}

	return 0;
}
