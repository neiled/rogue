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
    
  private:
    virtual void die() override;
    virtual bool is_player() override { return true;}
};
#endif
