#include "monster_factory.h"
#include "monster.h"
#include "tile.h"
#include "level.h"
#include <SDL2/SDL.h>

Monster* MonsterFactory::Build(Tile& tile)
{
  auto depth = tile.level().depth();
  auto type = MonsterFactory::calc_monster_type(depth);
  auto monster = new Monster(tile, type, Monster::MonsterState::Awake, calc_xp_level(depth));
  return monster;
}

Monster::MonsterType MonsterFactory::calc_monster_type(int depth)
{
  return Monster::MonsterType::Orc;
}

int MonsterFactory::calc_xp_level(int depth)
{
  //TODO: this needs some better logic
  return depth;
}
