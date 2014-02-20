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
};
#endif
