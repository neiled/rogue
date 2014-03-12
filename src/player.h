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
    int min_damage(Actor& other) override;
    void increase_xp(int amount);

    bool explore();
    virtual void set_tile(Tile& newTile) override;
    void add_seen_items();
    bool can_see_something_interesting(bool quiet = true) override;
    bool can_see_monster(bool quiet = true);
    bool can_see_unknown_item(bool quiet = true);
    bool can_see_interesting_tile(bool quiet = true);

  protected:
    virtual void pickup_items() override;
    
  private:
    virtual void die() override;
    virtual bool is_player() override { return true;}
    virtual void killed(Actor* other) override ;

    int32_t _xp;
    int32_t _max_xp;
    int32_t _min_xp;
    int32_t calc_max_xp();
    int32_t calc_min_xp();
    void increase_level();

    std::vector<Item*> _interesting_items_seen;
    std::vector<Tile*> _interesting_tiles_seen;
    
    bool _auto_pickup;


};
#endif
