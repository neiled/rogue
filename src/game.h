#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>
#include "sprite.h"

class World;

struct Game {
  Game();
  ~Game();

  private:
    void eventLoop();
    void update(World* world);
    void draw(Graphics* graphics, World* world);

    void delay();

};
#endif
