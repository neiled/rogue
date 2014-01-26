#include "game.h"


Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  _screen = SDL_CreateWindow("My Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
  eventLoop();
}

Game::~Game() {
  SDL_DestroyWindow(_screen);
  SDL_Quit();
}

void Game::eventLoop()
{
  SDL_Event event;
  bool running = true;
  while (running == true)
  {
    //fprintf(stderr, "test");
    const int start_time_ms = SDL_GetTicks();
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE)
            running = false;
          break;
        default:
          break;
      }

    }
    update();
    draw();
    const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
    int timeToDelay = 1000 / 60 - elapsed_time_ms;
    timeToDelay = timeToDelay < 0 ? 0 : timeToDelay;

    fprintf(stderr, "delaying for %d\n", timeToDelay);
    SDL_Delay(timeToDelay);
    fprintf(stderr, "finished delay\n");
  }

}

void Game::update()
{
}
void Game::draw()
{
}
   
