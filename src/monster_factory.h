#ifndef MONSTER_FACTORY_H
#define MONSTER_FACTORY_H 

#include "monster.h"

class Tile;

class MonsterFactory
{
public:
  static Monster* Build(Tile& tile);

private:
  static Monster::MonsterType calc_monster_type(int depth);
  static int calc_xp_level(int depth);
  static Monster* get_monster(Monster::MonsterType)
};
#endif
