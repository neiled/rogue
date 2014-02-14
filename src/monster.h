#ifndef MONSTER_H_
#define MONSTER_H_


#include <deque>
#include "actor.h"

class Tile;


class Monster : public Actor
{
  public:
    enum class MonsterType {Orc};
    enum class MonsterState {Asleep, Awake, Hunting};

    Monster(Tile& startTile, Monster::MonsterType type, Monster::MonsterState state);
    virtual ~Monster();
    void explore();
    
    virtual void update() override;

    Monster::MonsterType getMonsterType();
    
    
  private:
    Monster::MonsterType _monsterType;
    Monster::MonsterState _monsterState;

    bool can_see_player(const Player& player);

    virtual void die() override;
};
#endif
