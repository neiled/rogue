#ifndef MONSTER_FACTORY_H
#define MONSTER_FACTORY_H 

#include "monster.h"
#include <string>

class Tile;

class MonsterFactory
{
public:
  static Monster* Build(Tile& tile);

private:
  static MonsterType calc_monster_type(int depth);
  static int calc_xp_level(int depth);
  static Monster* get_monster(MonsterType, Tile& tile, int xp_level);
  static std::string get_name(MonsterType);
};
#endif
