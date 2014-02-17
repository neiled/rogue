#include <SDL2/SDL.h>
#include "level.h"
#include "monster.h"
#include "tile.h"
#include "player.h"
#include "a_star.h"
#include "item.h"

Monster::Monster(Tile& startTile, Monster::MonsterType type, Monster::MonsterState state)
{
  this->direction = static_cast<Actor::Direction>(Random::Between(0,3));
  setCurrentTile(startTile);
  _monster_type = type;
  _monsterState = state;
  _health = 10;
}

Monster::~Monster()
{
}

void Monster::update()
{
  if(dead())
    return;
  Player* player = level().player();
  if(_monsterState != Monster::MonsterState::Hunting)
  {
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
    hunt(*player);
  
}

void Monster::hunt(Player& player)
{
  _travelPath.clear();
  AStar searcher;
  _travelPath = searcher.plotPath(*_currentTile, *player.tile());
  if(_travelPath.empty() == false)
  {
    Commands::CMD dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
    _commandQueue.push_front(dirCommand);
  }
}


Monster::MonsterType Monster::getMonsterType()
{
  return _monster_type;
}

void Monster::die()
{
  _commandQueue.clear();
  _currentTile->removeActor();
  auto corpse = generate_corpse();
  if(corpse)
    _currentTile->add_item(corpse);
}

Item* Monster::generate_corpse()
{
  switch(_monster_type)
  {
    case MonsterType::Orc:
      return new Item(Item::ItemType::ORC_CORPSE);
      break;
    default:
      return nullptr;
  }
}
