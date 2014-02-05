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
  Renderer renderer(&graphics);
  int last_update_time = SDL_GetTicks();

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
          else if(event.key.keysym.sym == SDLK_UP)
            world.getPlayer()->moveUp();
          else if(event.key.keysym.sym == SDLK_DOWN)
            world.getPlayer()->moveDown();
          else if(event.key.keysym.sym == SDLK_LEFT)
            world.getPlayer()->moveLeft();
          else if(event.key.keysym.sym == SDLK_RIGHT)
            world.getPlayer()->moveRight();
          break;
        default:
          break;
      }

    }
    int current_time = SDL_GetTicks();
    update(&world, &renderer, current_time - last_update_time);
    last_update_time = current_time;
    draw(&graphics, &renderer, &world);

    delay(start_time_ms);

  }

}

void Game::delay(int start_time_ms)
{
  const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
  int timeToDelay = 1000 / 60 - elapsed_time_ms;
  timeToDelay = timeToDelay < 0 ? 0 : timeToDelay;

  SDL_Delay(timeToDelay);  
}

void Game::update(World* world, Renderer* renderer, int elapsed_time_ms)
{
  world->update();
  renderer->update(world, elapsed_time_ms);
  
}
void Game::draw(Graphics* graphics, Renderer* renderer, World* world)
{
  graphics->clearScreen();
  renderer->render(world->getCurrentLevel());
  renderer->render(world->getPlayer());
  graphics->render();
}
   
