#ifndef PLAYER_H_
#define PLAYER_H_


#include <deque>
#include "actor.h"

class Player : public Actor
{
  public:
    Player();
    virtual ~Player();
    void explore();
    virtual void update() override;
    
  private:
    virtual void die() override;
};
#endif
