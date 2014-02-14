#include "game.h"
#include "graphics.h"
#include "world.h"
#include "player.h"
#include "renderer.h"


Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  eventLoop();
}

Game::~Game() {
  SDL_Quit();
}

void Game::eventLoop()
{
  SDL_Log("Creating Graphics");
  Graphics graphics;
  SDL_Event event;
  SDL_Log("Creating world");
  World world;
  Player& player = world.getPlayer();
  SDL_Log("Creating renderer");
  Renderer renderer(&graphics);
  SDL_Log("Done renderer");
  CommandProcessor cProc;
  int last_update_time = SDL_GetTicks();

  update(&world);

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
            player.pushCommand(Commands::CMD::CMD_MOVE_UP);
          else if(event.key.keysym.sym == SDLK_DOWN)
            player.pushCommand(Commands::CMD::CMD_MOVE_DOWN);
          else if(event.key.keysym.sym == SDLK_LEFT)
            player.pushCommand(Commands::CMD::CMD_MOVE_LEFT);
          else if(event.key.keysym.sym == SDLK_RIGHT)
            player.pushCommand(Commands::CMD::CMD_MOVE_RIGHT);
          else if(event.key.keysym.sym == SDLK_o)
            player.pushCommand(Commands::CMD::CMD_EXPLORE);
          else if(event.key.keysym.sym == SDLK_p)
            player.clearCommands();
          break;
        default:
          break;
      }

    }

    if(player.hasCommands())
    {
      cProc.Process(player.popCommand(), &world);
      update(&world);

    }

    int current_time = SDL_GetTicks();
    updateGraphics(&world, &renderer, current_time - last_update_time);
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

void Game::update(World* world)
{
  world->update();
  
}
void Game::updateGraphics(World* world, Renderer* renderer, int elapsed_time_ms)
{
  world->updateGraphics();
  renderer->update(world, elapsed_time_ms);
  
}
void Game::draw(Graphics* graphics, Renderer* renderer, World* world)
{
  graphics->clearScreen();
  renderer->render(world->getCurrentLevel());
  renderer->render(world->getPlayer());
  graphics->render();
}
   
