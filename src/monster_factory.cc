#include "monster_factory.h"
#include "monster.h"
#include "tile.h"
#include "level.h"
#include <SDL2/SDL.h>

Monster* MonsterFactory::Build(Tile& tile)
{
  auto depth = tile.level().depth();
  auto type = MonsterFactory::calc_monster_type(depth);
  auto name = MonsterFactory::get_name(type);
  auto monster = new Monster(name, tile, type, Monster::MonsterState::Awake, calc_xp_level(depth));
  return monster;
}

Monster::MonsterType MonsterFactory::calc_monster_type(int depth)
{
  int random = Random::Between(0,1);
  if(random < 1)
    return Monster::MonsterType::Orc;
  else
    return Monster::MonsterType::Devil;
}

int MonsterFactory::calc_xp_level(int depth)
{
  //TODO: this needs some better logic
  return depth;
}

std::string MonsterFactoy::get_name(Monster::MonsterType type)
{
  switch(type)
  {
    case Monster::MonsterType::Orc:
      return "Orc";
    case Monster::MonsterType::Devil:
      return "Devil";
    default:
      return "Unknown type";
  }
}
