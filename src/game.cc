#include "game.h"
#include "graphics.h"
#include "world.h"


Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  eventLoop();
}

Game::~Game() {
  SDL_Quit();
}

void Game::eventLoop()
{
  Graphics graphics;
  SDL_Event event;
  World world;

  _sprite.reset(new Sprite(&graphics, "content/MyChar.bmp", 0, 0, 32, 32));
  bool running = true;
  while (running == true)
  {
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
    update(&world);
    draw(&graphics, &world);
    const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
    int timeToDelay = 1000 / 60 - elapsed_time_ms;
    timeToDelay = timeToDelay < 0 ? 0 : timeToDelay;

    //fprintf(stderr, "delaying for %d\n", timeToDelay);
    SDL_Delay(timeToDelay);
    //fprintf(stderr, "finished delay\n");
    //const float seconds_per_frame = (SDL_GetTicks() - start_time_ms )/ 1000.0;
    //const float fps = 1 / seconds_per_frame;
    //fprintf(stderr, "fps=%f\n", fps);
  }

}

void Game::update(World* world)
{
  
}
void Game::draw(Graphics* graphics, World* world)
{
  graphics->clearScreen();
  
  _sprite->draw(320, 240);
  graphics->render();
}
   
