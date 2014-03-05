#ifndef MONSTER_H_
#define MONSTER_H_


#include <deque>
#include "actor.h"

class Tile;
class Player;
class Item;


class Monster : public Actor
{
  public:
    enum class MonsterType {Orc, Devil};
    enum class MonsterState {Asleep, Awake, Hunting, Wandering};

    Monster(std::string name, Tile& startTile, Monster::MonsterType type, Monster::MonsterState state, int xp_level);
    virtual ~Monster();
    void explore();
    
    virtual void update() override;

    Monster::MonsterType monster_type();
    
    
  private:
    Monster::MonsterType _monster_type;
    Monster::MonsterState _monsterState;

    bool can_see_player(const Player& player);

    void hunt(Player& player);
    Item* generate_corpse();
    void populate_inventory();
    virtual void die() override;
    virtual int max_health() override;
    virtual bool is_player() override { return false;}
    virtual void killed(Actor* other) override {}

};
#endif
