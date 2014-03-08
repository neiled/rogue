#ifndef PLAYER_H_
#define PLAYER_H_


#include <deque>
#include "actor.h"

class Player : public Actor
{
  public:
    Player();
    virtual ~Player();
    virtual void update() override;
    virtual int max_health() override;
  
    int32_t xp();
    int32_t max_xp();
    int32_t min_xp();
    int max_damage(Actor& other) override;
    void increase_xp(int amount);

    bool explore();
    virtual void set_tile(Tile& newTile) override;
    bool add_seen_items();

  protected:
    virtual void pickup_items() override;
    
  private:
    virtual void die() override;
    virtual bool is_player() override { return true;}
    virtual void killed(Actor* other) override ;
    bool can_see_something_interesting();

    int32_t _xp;
    int32_t _max_xp;
    int32_t _min_xp;
    int32_t calc_max_xp();
    int32_t calc_min_xp();
    void increase_level();

    std::vector<Item*> _items_seen;


};
#endif
