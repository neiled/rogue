#include "monster.h"
#include "tile.h"
#include <SDL2/SDL.h>

Monster::Monster(std::shared_ptr<Tile> startTile, Monster::MonsterType type, Monster::MonsterState state)
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
  SDL_Log("Killing monster");
  _currentTile->removeActor();
  SDL_Log("Killed monster");
  //TODO: Free up memory this monster used....
}
