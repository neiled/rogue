#ifndef MONSTER_H_
#define MONSTER_H_

class Level;
class Tile;

#include <deque>
#include "commands.h"
#include "world.h"
#include "actor.h"


class Monster : Actor
{
  public:
    Monster();
    virtual ~Monster();
    void explore();
    
    enum class MonsterType {Orc};
    
  private:
  Monster::MonsterType _monsterType;
};
#endif
