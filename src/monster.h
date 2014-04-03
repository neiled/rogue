#ifndef MONSTER_H_
#define MONSTER_H_


#include <deque>
#include "actor.h"
#include "game_types.h"

class Tile;
class Player;
class Item;


class Monster : public Actor
{
  public:

    Monster(std::string name, Tile& startTile, MonsterType type, MonsterState state, int xp_level, float speed);
    virtual ~Monster();
    void explore();
    
    //virtual void update() override;
    void think();

    MonsterType monster_type();

    virtual int max_damage(Actor& other) override;
    virtual int min_damage(Actor& other) override;
    
    
  private:
    MonsterType _monster_type;
    MonsterState _monsterState;

    void look_for_player();
    void wander();
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
