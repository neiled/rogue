#include <SDL2/SDL.h>
#include "level.h"
#include "monster.h"
#include "tile.h"
#include "player.h"
#include "a_star.h"
#include "item.h"
#include "item_factory.h"
#include "game_types.h"

Monster::Monster(std::string name, Tile& startTile, MonsterType type, MonsterState state, int xp_level)
  : Actor(name, xp_level), _monster_type(type), _monsterState(state)
{
  this->direction = static_cast<Actor::Direction>(Random::Between(0,3));
  set_tile(startTile);
  //_monster_type = type;
  //_monsterState = state;
  _attributes[Attribute::HEALTH] = max_health();
  _attributes[Attribute::CON] = max_health();
  _previous_health = max_health();
  populate_inventory();
}

Monster::~Monster()
{
}

void Monster::start_turn()
{
  Actor::start_turn();
  if(dead())
    return;
  Player* player = level().player();
  if(_monsterState != MonsterState::Hunting)
  {
    look_for_player();
  }
  
  if(_monsterState == MonsterState::Hunting)
    hunt(*player);
  if(_monsterState == MonsterState::Wandering)
  {
    wander();
  }
  
}

void Monster::end_turn()
{
  Actor::end_turn();
}

void Monster::look_for_player()
{
  if(!level().player())
    return;

  if(can_see_actor(*level().player()))
  {
    _monsterState = MonsterState::Hunting;
  }
}

void Monster::wander()
{
  if(_travelPath.empty())
  {
    auto target_tile = level().get_near_random_of_type(*_currentTile, 5, TileType::Floor);
    AStar searcher;
    _travelPath = searcher.plotPath(*_currentTile, *target_tile, 100);
  }
  if(_travelPath.empty() == false)
  {
    Commands::CMD dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
    _travelPath.pop_front();
    _commandQueue.push_front(dirCommand);
  }  
}
void Monster::hunt(Player& player)
{
  _travelPath.clear();
  AStar searcher;
  _travelPath = searcher.plotPath(*_currentTile, *player.tile(), 200);
  if(_travelPath.empty() == false)
  {
    Commands::CMD dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
    _commandQueue.push_front(dirCommand);
  }
}


MonsterType Monster::monster_type()
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
  switch(_monster_type)
  {
    case MonsterType::Orc:
      return ItemFactory::Build(ItemType::CORPSE, ItemSubtype::CORPSE_ORC);
    case MonsterType::Devil:
      return ItemFactory::Build(ItemType::CORPSE, ItemSubtype::CORPSE_DEVIL);
    case MonsterType::Skeleton:
      return ItemFactory::Build(ItemType::CORPSE, ItemSubtype::CORPSE_SKELETON);
    default:
      SDL_Log("Need to generate a corpse for this monster type");
      return nullptr;
  }
}

int Monster::max_health()
{
  switch(_monster_type)
  {
    case MonsterType::Orc:
      return 10 * xp_level();
    case MonsterType::Devil:
      return 15 * xp_level();
    case MonsterType::Skeleton:
      return 10 * xp_level();
  }
}

int Monster::max_damage(Actor& other)
{
  switch(_monster_type)
  {
    case MonsterType::Orc:
      return 6 * xp_level();
    case MonsterType::Devil:
      return 3 * xp_level();
    case MonsterType::Skeleton:
      return 2 * xp_level();
  }
}

int Monster::min_damage(Actor& other)
{
  switch(_monster_type)
  {
    case MonsterType::Orc:
      return 2 * xp_level();
    case MonsterType::Devil:
      return 1 * xp_level();
    case MonsterType::Skeleton:
      return 1 * xp_level();
  }
}

void Monster::populate_inventory()
{
  //TODO: This should be populated when the player sees the monster and use their current luck score
  if(Random::Between(0,100) < 33)
    _inventory.add(ItemFactory::Build(monster_type(), xp_level()));
  if(Random::Between(0,100) < 12)
    _inventory.add(ItemFactory::Build(monster_type(), xp_level()));
}
