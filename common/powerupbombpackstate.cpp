#include "powerupbombpackstate.h"

using namespace Common;

PowerUpBombPackState::PowerUpBombPackState(UniqueIdCreator &creator, const Point &position) :
    PowerUpState(creator, position),
    m_BombsInPackage(5)
{ }
