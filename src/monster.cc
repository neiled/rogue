#include "monster.h"
#include "tile.h"

Monster::Monster(Tile* startTile, Monster::MonsterType type, Monster::MonsterState state)
{
  setCurrentTile(startTile);
  _monsterType = type;
  _monsterState = state;
  _health = 100;
}

Monster::~Monster()
{
}
Monster::MonsterType Monster::getMonsterType()
{
  return _monsterType;
}

void Monster::die()
{
  _currentTile->removeActor();
  //TODO: Free up memory this monster used....
}
