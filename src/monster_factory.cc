#include "monster_factory.h"
#include "monster.h"
#include "tile.h"
#include "level.h"
#include <SDL2/SDL.h>

Monster* MonsterFactory::Build(Tile& tile)
{
  auto depth = tile.level().depth();
  auto type = MonsterFactory::calc_monster_type(depth);
  //auto name = MonsterFactory::get_name(type);
  //auto monster = new Monster(name, tile, type, MonsterState::Awake, calc_xp_level(depth));
  return MonsterFactory::get_monster(type, tile, calc_xp_level(depth));
}

MonsterType MonsterFactory::calc_monster_type(int depth)
{
  int random = Random::Between(0,1);
  if(random < 1)
    return MonsterType::Orc;
  else
    return MonsterType::Devil;
}

int MonsterFactory::calc_xp_level(int depth)
{
  //TODO: this needs some better logic
  return depth;
}

Monster* MonsterFactory::get_monster(MonsterType type, Tile& tile, int xp_level)
{
  auto name = MonsterFactory::get_name(type);  
  switch(type)
  {
    case MonsterType::Orc:
      return new Monster(name, tile, type, MonsterState::Awake, xp_level);
    case MonsterType::Devil:
      return new Monster(name, tile, type, MonsterState::Wandering, xp_level);
    default:
      SDL_Log("Need to add this new monster type to MonsterFactory::get_monster");
      break;
  }
}

std::string MonsterFactory::get_name(MonsterType type)
{
  switch(type)
  {
    case MonsterType::Orc:
      return "Orc";
    case MonsterType::Devil:
      return "Devil";
    default:
      return "Unknown type";
  }
}
