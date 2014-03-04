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
  end_turn();
}

void Game::eventLoop()
{
  SDL_Log("Creating Graphics");
  Graphics graphics;
  SDL_Event event;
  SDL_Log("Creating renderer");
  Renderer renderer(&graphics);
  SDL_Log("Done renderer");
  CommandProcessor cProc;
  end_turn();
  //int last_update_time = SDL_GetTicks();


  bool running = true;
  while (running == true)
  {
    Player* player = _world.player();
    //const int start_time_ms = SDL_GetTicks();
    draw(&graphics, &renderer);
    SDL_WaitEvent(&event);

    decode_event(event, graphics, renderer);

    if(_state == GameState::GAME && player->dead())
      _state = GameState::DEAD;
    else
    {
      while(player->hasCommands())
      {
        if(cProc.Process(player->popCommand(), *player))
        {
          end_turn();
          draw(&graphics, &renderer);
        }
      }
    }


    //int current_time = SDL_GetTicks();
    //updateGraphics(&renderer);
    //last_update_time = current_time;

    //delay(start_time_ms);

    if(_state == GameState::STARTING)
    {
      reset();
    }
    if(_state == GameState::STOP)
      running = false;

  }

}

//draw the screen
//let the monsters have their turn
//update the camera
//check the player has moved down a level
//update the turn count
//

void Game::end_turn()
{
  ++_turn;
  _world.update();
  Messages::Push();
}

void Game::decode_event(SDL_Event& event, Graphics& graphics, Renderer& renderer)
{
  switch(event.type)
  {
    case SDL_KEYDOWN:
    {
      auto decoded = _decoders[_state]->Decode(event.key.keysym.sym, *this);
      if(decoded)
      {
        draw(&graphics, &renderer);
      }
      break;
    }
    default:
      break;
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

void Game::draw(Graphics* graphics, Renderer* renderer)
{
  renderer->update(&_world);
  graphics->clearScreen();
  renderer->render(*this);
  graphics->render();
}
   
