#ifndef MONSTER_H_
#define MONSTER_H_

class Level;
class Tile;

#include <deque>
#include "commands.h"
#include "world.h"
#include "actor.h"


class Monster : public Actor
{
  public:
    enum class MonsterType {Orc};
    enum class MonsterState {Asleep, Awake, Hunting};

    Monster(Tile* startTile, Monster::MonsterType type, Monster::MonsterState state);
    virtual ~Monster();
    void explore();

    Monster::MonsterType getMonsterType();
    
    
  private:
    Monster::MonsterType _monsterType;
    Monster::MonsterState _monsterState;
};
#endif
