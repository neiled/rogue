#ifndef PLAYER_H_
#define PLAYER_H_

class Level;
class Tile;

#include <deque>
#include "commands.h"
#include "world.h"
#include "actor.h"


class Player : Actor
{
  public:
    Player();
    virtual ~Player();
    void explore();
    
  private:
};
#endif
