#include "level.h"
#include "monster.h"
#include "tile.h"
#include <SDL2/SDL.h>

Monster::Monster(Tile& startTile, Monster::MonsterType type, Monster::MonsterState state)
{
  setCurrentTile(startTile);
  _monsterType = type;
  _monsterState = state;
  _health = 100;
}

Monster::~Monster()
{
}

void Monster::update()
{
  if(_monsterState != Monster::MonsterState::Hunting)
  {
    Player* player = level().player();
    if(!player)
      return;
    if(can_see_player(*player))
    {
      _monsterState = Monster::MonsterState::Hunting;
    }
  }
  
  if(_monsterState == Monster::MonsterState::Hunting)
  {
    //TODO: Move towards player
  }
  
}

bool Monster::can_see_player(const Player& player)
{
  return false; //TODO: fixme
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

