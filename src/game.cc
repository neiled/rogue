#include "game.h"
#include "graphics.h"
#include "world.h"
#include "actor.h"
#include "player.h"
#include "renderer.h"
#include "messages.h"
#include "item_factory.h"
#include "command_decoder_game.h"
#include "command_decoder_inventory.h"
#include "command_decoder_dead.h"


Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  ItemFactory::Init();
  _world.init();
  _decoders[Game::GameState::GAME] = new CommandDecoderGame();
  _decoders[Game::GameState::MENU_INVENTORY] = new CommandDecoderInventory();
  _decoders[Game::GameState::DEAD] = new CommandDecoderDead();
  _state = GameState::GAME;
  eventLoop();
}

Game::~Game() {
  SDL_Quit();
}

void Game::reset()
{
  _world = World();
  _world.init();
  Messages::Clear();
  _state = GameState::GAME;
}

void Game::eventLoop()
{
  SDL_Log("Creating Graphics");
  Graphics graphics;
  SDL_Event event;
  SDL_Log("Creating world");
  Player* player = _world.player();
  SDL_Log("Creating renderer");
  Renderer renderer(&graphics);
  SDL_Log("Done renderer");
  CommandProcessor cProc;
  //int last_update_time = SDL_GetTicks();

  update(renderer);

  bool running = true;
  while (running == true)
  {
    const int start_time_ms = SDL_GetTicks();
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_KEYDOWN:
          _decoders[_state]->Decode(event.key.keysym.sym, *this);
          break;
        default:
          break;
      }

    }

    if(_state == GameState::GAME && player->dead())
      _state = GameState::DEAD;
    else
    {
      if(player->hasCommands())
      {
        if(cProc.Process(player->popCommand(), *player))
          update(renderer);
      }
    }


    //int current_time = SDL_GetTicks();
    //updateGraphics(&renderer);
    //last_update_time = current_time;
    draw(&graphics, &renderer);

    delay(start_time_ms);

    if(_state == GameState::STARTING)
    {
      reset();
      player = _world.player();
      update(renderer);
    }
    if(_state == GameState::STOP)
      running = false;

  }

}

void Game::state(GameState state)
{
  _state = state;
}

Game::GameState Game::state()
{
  return _state;
}

Player* Game::player()
{
  return _world.player();
}


Level* Game::level()
{
  return &_world.getCurrentLevel();
}

void Game::delay(int start_time_ms)
{
  const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
  int timeToDelay = 1000 / 30 - elapsed_time_ms;
  timeToDelay = timeToDelay < 0 ? 0 : timeToDelay;

  SDL_Delay(timeToDelay);  
}

void Game::update(Renderer& renderer)
{
  ++_turn;
  _world.update();
  renderer.update(&_world);
}
//void Game::updateGraphics(Renderer* renderer, int elapsed_time_ms)
//{
  //_world.updateGraphics();
  
//}
void Game::draw(Graphics* graphics, Renderer* renderer)
{
  auto player = _world.player();
  graphics->clearScreen();
  renderer->render(*this);
  graphics->render();
}
   
