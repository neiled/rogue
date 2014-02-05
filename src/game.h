#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>
#include "sprite.h"
#include "renderer.h"

class World;

struct Game {
  Game();
  ~Game();

  private:
    void eventLoop();
    void update(World* world,Renderer* renderer,  int elapsed_time_ms);
    void draw(Graphics* graphics, Renderer* renderer, World* world);

    void delay(int start_time_ms);

};
#endif
