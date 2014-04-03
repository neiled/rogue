#include "monster_factory.h"
#include "monster.h"
#include "tile.h"
#include "level.h"
#include <SDL2/SDL.h>

Monster* MonsterFactory::Build(Tile& tile)
{
  auto depth = tile.level().depth();
  auto type = MonsterFactory::calc_monster_type(depth);
  return MonsterFactory::get_monster(type, tile, calc_xp_level(depth));
}

MonsterType MonsterFactory::calc_monster_type(int depth)
{
  int random = Random::Between(0,100);
  if(random < 33)
    return MonsterType::Orc;
  else if(random < 66)
    return MonsterType::Skeleton;
  else
    return MonsterType::Devil;
}

int MonsterFactory::calc_xp_level(int depth)
{
  if(depth == 1)
    return 1;
  int min_level = depth-2;
  if(min_level < 1) min_level = 1;
  
  int max_level = depth+2;
  
  return Random::BetweenNormal(min_level, max_level);
}

Monster* MonsterFactory::get_monster(MonsterType type, Tile& tile, int xp_level)
{
  auto name = MonsterFactory::get_name(type);  
  switch(type)
  {
    case MonsterType::Orc:
      return new Monster(name, tile, type, MonsterState::Awake, xp_level, 0.5);
    case MonsterType::Devil:
      return new Monster(name, tile, type, MonsterState::Wandering, xp_level, 1);
    case MonsterType::Skeleton:
      return new Monster(name, tile, type, MonsterState::Awake, xp_level, 2);
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
    case MonsterType::Skeleton:
      return "Skeleton";
    default:
      return "Unknown type";
  }
}
