#include "monster.h"

Monster::Monster(Tile* startTile, Monster::MonsterType type, Monster::MonsterState state)
{
  setCurrentTile(startTile);
  _monsterType = type;
  _monsterState = state;
}

Monster::~Monster()
{
}
Monster::MonsterType Monster::getMonsterType()
{
  return _monsterType;
}
