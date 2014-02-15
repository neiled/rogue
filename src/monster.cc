#include "level.h"
#include "monster.h"
#include "tile.h"
#include "player.h"
#include "a_star.h"
#include <SDL2/SDL.h>

Monster::Monster(Tile& startTile, Monster::MonsterType type, Monster::MonsterState state)
{
  this->direction = static_cast<Actor::Direction>(Random::Between(0,3));
  setCurrentTile(startTile);
  _monsterType = type;
  _monsterState = state;
  _health = 10;
}

Monster::~Monster()
{
}

void Monster::update()
{
  //SDL_Log("Monster::update");
  if(dead())
    return;
  //SDL_Log("not dead");
  Player* player = level().player();
  //SDL_Log("got player");
  if(_monsterState != Monster::MonsterState::Hunting)
  {
    //SDL_Log("not hunting");
    if(!player)
    {
      return;
    }
    if(can_see_actor(*player))
    {
      _monsterState = Monster::MonsterState::Hunting;
    }
  }
  
  if(_monsterState == Monster::MonsterState::Hunting)
  {
    _travelPath.clear();
    AStar searcher;
    _travelPath = searcher.plotPath(*_currentTile, *player->getCurrentTile());
    if(_travelPath.empty() == false)
    {
      Commands::CMD dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
      _commandQueue.push_front(dirCommand);
    }
  }
  
}


Monster::MonsterType Monster::getMonsterType()
{
  return _monsterType;
}

void Monster::die()
{
  _commandQueue.clear();
  _currentTile->removeActor();
}

