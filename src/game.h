#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>

struct SDL_Surface;

struct Game {
  Game();
  ~Game();

  private:
    void eventLoop();
    void update();
    void draw();

    SDL_Window *_screen;
};
#endif
