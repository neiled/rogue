#include <SDL2/SDL.h>
#include "level.h"
#include "monster.h"
#include "tile.h"
#include "player.h"
#include "a_star.h"
#include "item.h"
#include "item_factory.h"

Monster::Monster(std::string name, Tile& startTile, Monster::MonsterType type, Monster::MonsterState state, int xp_level)
  : Actor(name, max_health(), xp_level)
{
  this->direction = static_cast<Actor::Direction>(Random::Between(0,3));
  setCurrentTile(startTile);
  _monster_type = type;
  _monsterState = state;
  populate_inventory();
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


Monster::MonsterType Monster::monster_type()
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

  drop_items();
}

Item* Monster::generate_corpse()
{
  //TODO: This should use the prototypes from item builder
  switch(_monster_type)
  {
    case MonsterType::Orc:
      return new Item("Orc Corpse", Item::ItemType::CORPSE, Item::ItemSubtype::CORPSE_ORC);
      break;
    case MonsterType::Devil:
      return new Item("Devil Corpse", Item::ItemType::CORPSE, Item::ItemSubtype::CORPSE_DEVIL);
    default:
      SDL_Log("Need to generate a corpse for this monster type");
      return nullptr;
  }
}

int Monster::max_health()
{
  return 10;
}

void Monster::populate_inventory()
{
  //TODO: This should be populated when the player sees the monster and use their current luck score
  if(Random::Between(0,100) < 25)
    _inventory.add(ItemFactory::Build(monster_type(), xp_level()));
  if(Random::Between(0,100) < 12)
    _inventory.add(ItemFactory::Build(monster_type(), xp_level()));
}
