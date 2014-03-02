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
    void increase_xp(int amount);

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

};
#endif
