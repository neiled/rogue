#ifndef GAME_H_
#define GAME_H_

#include <boost/scoped_ptr.hpp>
#include "sprite.h"


struct Game {
  Game();
  ~Game();

  private:
    void eventLoop();
    void update();
    void draw(Graphics* graphics);

    boost::scoped_ptr<Sprite> _sprite;

};
#endif
