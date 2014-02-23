#include "monster_factory.h"
#include "monster.h"
#include "tile.h"
#include "level.h"
#include <SDL2/SDL.h>

Monster* MonsterFactory::Build(Tile& tile)
{
  auto type = MonsterFactory::calc_monster_type(tile.level().depth());
  auto monster = new Monster(tile, type, Monster::MonsterState::Awake);
  return monster;
}

Monster::MonsterType MonsterFactory::calc_monster_type(int depth)
{
  return Monster::MonsterType::Orc;
}
