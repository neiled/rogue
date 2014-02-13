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

virtual void Monster::update() override
{
  if(_monsterState != Monster::MonsterState::Hunting)
  {
    if(can_see_player(level()->player()))
    {
      _monsterState = Monster::MonsterState::Hunting;
    }
  }
  
  if(_monsterState == Monster::MonsterState::Hunting)
  {
    //TODO: Move towards player
  }
  
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

